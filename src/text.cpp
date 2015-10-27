#include "text.h"
#include <stdio.h>
#include <string.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Undefined;
using v8::FunctionTemplate;

IText::IText() 
{
	hwnd = NULL;
}
IText::~IText() {}

void IText::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IText"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosx", _setPosx);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosy", _setPosy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setSize", _setSize);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setValue", _setValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", _getValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "appendText", _appendText);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IText"),tpl->GetFunction());
}

void IText::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* obj = new IText();
	// Create Text
	obj->hwnd = IupText(NULL);
	// Set Position
	if (args.Length()>0 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CX",*str);
	}
	if (args.Length()>1 && args[1]->IsNumber()) {
		Local<String> tt = args[1]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CY",*str);
	}
	// Set size
	if (args.Length()>3 && args[2]->IsNumber() && args[3]->IsNumber()) {
		int ww = args[2]->Int32Value();
		int hh = args[3]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"%dx%d", ww, hh);
		IupSetStrAttribute(obj->hwnd, "RASTERSIZE", buf);
	}
	// set readonly
	if (args.Length()==5 && args[4]->IsNumber()) {
		int rr = args[4]->Int32Value();
		if (rr == 1) {
			IupSetStrAttribute(obj->hwnd, "READONLY", "YES");
		}
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IText::_setPosx(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(txt->hwnd,"CX",*str);
	} else {
		printf("setPosx arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void IText::_setPosy(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(txt->hwnd,"CY",*str);
	} else {
		printf("setPosy arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void IText::_setSize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsNumber()) {
		int ww = args[0]->Int32Value();
		int hh = args[1]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"%dx%d", ww, hh);
		IupSetStrAttribute(txt->hwnd, "RASTERSIZE", buf);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IText::_setValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(txt->hwnd,"VALUE",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IText::_getValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	char* sRet = IupGetAttribute(txt->hwnd,"VALUE");
	args.GetReturnValue().Set(String::NewFromUtf8(isolate, sRet));
}

void IText::_appendText(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IText* txt = ObjectWrap::Unwrap<IText>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(txt->hwnd,"APPEND",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
