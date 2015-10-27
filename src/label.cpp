#include "label.h"
#include <stdio.h>
#include <string.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Undefined;
using v8::FunctionTemplate;

ILabel::ILabel() 
{
	hwnd = NULL;
}
ILabel::~ILabel() {}

void ILabel::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "ILabel"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosx", _setPosx);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosy", _setPosy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setTitle", _setTitle);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setImage", _setImage);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "ILabel"),tpl->GetFunction());
}

void ILabel::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ILabel* obj = new ILabel();
	// Create Label
	if (args.Length()==0) {
		obj->hwnd = IupLabel("");
	} else if (args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		obj->hwnd = IupLabel(*str);
	} else {
		obj->hwnd = IupLabel("");
	}
	// Set Position
	if (args.Length()>1 && args[1]->IsNumber()) {
		Local<String> tt = args[1]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CX",*str);
	}
	if (args.Length()>2 && args[2]->IsNumber()) {
		Local<String> tt = args[2]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"CY",*str);
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void ILabel::_setPosx(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ILabel* lbl = ObjectWrap::Unwrap<ILabel>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(lbl->hwnd,"CX",*str);
	} else {
		printf("setPosx arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ILabel::_setPosy(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ILabel* lbl = ObjectWrap::Unwrap<ILabel>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(lbl->hwnd,"CY",*str);
	} else {
		printf("setPosy arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ILabel::_setTitle(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ILabel* lbl = ObjectWrap::Unwrap<ILabel>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(lbl->hwnd,"TITLE",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ILabel::_setImage(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ILabel* lbl = ObjectWrap::Unwrap<ILabel>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(lbl->hwnd,"IMAGE",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));		
}
	
}
