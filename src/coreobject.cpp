#include "coreobject.h"
#include <string.h>
#include <stdio.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::HandleScope;
using v8::Isolate;
using v8::Number;
using v8::Persistent;
using v8::String;
using v8::Value;
using v8::Undefined;
using v8::Integer;
using v8::Array;
using v8::Handle;
using v8::TryCatch;
using v8::Context;
using v8::Script;

Persistent<Function> CoreObject::constructor;
int CoreObject::bInit = 0;

CoreObject::CoreObject() {}
CoreObject::~CoreObject() {}

void CoreObject::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "CoreObject"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "CoreObject"),tpl->GetFunction());
}

void CoreObject::New(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	if (args.IsConstructCall()) {
		// Invoked as constructor: 'new CoreObject(...)'
		if (bInit==0)
		{
			int argc = args.Length();
			Handle<Value>* initArgs = new Handle<Value>[argc];
			for(int i=0; i<argc; i++) {
				initArgs[i] = args[i];
			}
			Local<Value> initObj = args.This()->Get(String::NewFromUtf8(isolate,"init"));
			v8::Function *initFn = v8::Function::Cast(*initObj);
			v8::TryCatch tc;
			initFn->Call(args.This(), argc, initArgs);
			if(tc.HasCaught()) {
				printf("call init error\n");
			}
			delete initArgs;
		}
		args.GetReturnValue().Set(args.This());
	} else {
		// Invoked as plain function 'CoreObject(...)', turn into construct call.
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		args.GetReturnValue().Set(cons->NewInstance());
	}
}
	
// extend class constructor
void CoreObject::extendCallHandler(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	Local<Object> argsData = args.Data()->ToObject(isolate);
	Handle<Object> baseClass = argsData->Get(String::NewFromUtf8(isolate,"baseClass"))->ToObject();
	Handle<Object> subClass = argsData->Get(String::NewFromUtf8(isolate,"subClass"))->ToObject();

	// create new object
	bInit--;
	Local<Object> result = Local<Object>::Cast(baseClass->CallAsConstructor(0,NULL));
	bInit++;
	
	// Find superWrapMethod function
	Local<Function> swMethod = Local<Function>::Cast(isolate->GetCurrentContext()->Global()->Get(String::NewFromUtf8(isolate,"__superWrapMethod")));
	// copy subclass methods
	Local<Array> ns2 = subClass->GetPropertyNames();
	for (int j=0;j<ns2->Length();j++) {
		Local<String> n2 = ns2->Get(j)->ToString(isolate);
		Local<Value> propVal = subClass->Get(n2);
		Local<Value> basePropVal = result->Get(n2);
		if (propVal->IsFunction()) {
			Local<Value> swArgv[2];
			swArgv[0] = propVal;
			swArgv[1] = basePropVal;
			propVal = swMethod->Call(result,2,swArgv);
			result->Set(n2,propVal);
		} else {
			result->Set(n2,propVal);
		}
	}
		
	// call init
	if (bInit==0)
	{
		int argc = args.Length();
		Handle<Value>* initArgs = new Handle<Value>[argc];
		for(int i=0; i<argc; i++) {
			initArgs[i] = args[i];
		}
		Local<Value> initObj = result->Get(String::NewFromUtf8(isolate,"init"));
		v8::Function *initFn = v8::Function::Cast(*initObj);
		v8::TryCatch tc;
		initFn->Call(result, argc, initArgs);
		if(tc.HasCaught()) {
			printf("call init error\n");
		}
		delete initArgs;
	}
	args.GetReturnValue().Set(result);
}

void CoreObject::extend(const FunctionCallbackInfo<Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	Handle<Object> baseClass = args.This();
	Handle<Object> subClass = args[0]->ToObject(isolate);
	Handle<Object> data = Object::New(isolate);
	data->Set(String::NewFromUtf8(isolate,"baseClass"), baseClass);
	data->Set(String::NewFromUtf8(isolate,"subClass"), subClass);
	
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate);
	tpl->SetCallHandler(extendCallHandler,data);
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	Local<Function> ctor = tpl->GetFunction();
	
	Local<FunctionTemplate> extend = FunctionTemplate::New(isolate,CoreObject::extend);
	ctor->Set(String::NewFromUtf8(isolate,"extend"), extend->GetFunction());
		
	// copy static methods
	Local<Array> ns1 = baseClass->GetPropertyNames();
	for (int i=0;i<ns1->Length();i++) {
		Local<String> n1 = ns1->Get(i)->ToString(isolate);
		uint8_t buff[32];
		memset(buff,0,32);
		n1->WriteOneByte(buff);
		if(strcmp((char*)buff,"extend")==0) continue;
		Local<Value> propVal = baseClass->Get(n1);
		ctor->Set(n1,propVal);
	}
	args.GetReturnValue().Set(ctor);
}
	
void CoreObject::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	CoreObject* obj = new CoreObject();
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

}
