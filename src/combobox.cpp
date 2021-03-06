#include "combobox.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Undefined;
using v8::FunctionTemplate;
using v8::Integer;

IComboBox::IComboBox() 
{
	hwnd = NULL;
}
IComboBox::~IComboBox() {}

void IComboBox::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IComboBox"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosx", _setPosx);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setPosy", _setPosy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setSize", _setSize);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", _getValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "appendItem", _appendItem);
	NODE_SET_PROTOTYPE_METHOD(tpl, "removeItem", _removeItem);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getCount", _getCount);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getItemString", _getItemString);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IComboBox"),tpl->GetFunction());
}

void IComboBox::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* obj = new IComboBox();
	// Create List
	obj->hwnd = IupList(NULL);
	// Set as combobox
	IupSetStrAttribute(obj->hwnd,"DROPDOWN","YES");
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
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IComboBox::_setPosx(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(cb->hwnd,"CX",*str);
	} else {
		printf("setPosx arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void IComboBox::_setPosy(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		IupSetStrAttribute(cb->hwnd,"CY",*str);
	} else {
		printf("setPosy arg error\n");
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void IComboBox::_setSize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==2 && args[0]->IsNumber() && args[1]->IsNumber()) {
		int ww = args[0]->Int32Value();
		int hh = args[1]->Int32Value();
		char buf[16];
		memset(buf,0,16);
		sprintf(buf,"%dx%d", ww, hh);
		IupSetStrAttribute(cb->hwnd, "RASTERSIZE", buf);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IComboBox::_getValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	int nRet = IupGetInt(cb->hwnd,"VALUE");
	args.GetReturnValue().Set(Integer::New(isolate, nRet));
}

void IComboBox::_appendItem(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		IupSetAttribute(cb->hwnd,"APPENDITEM",*str);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IComboBox::_removeItem(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==1 && args[0]->IsNumber()) {
		int ii = args[0]->Int32Value();
		if (ii<1) {
			IupSetAttribute(cb->hwnd,"REMOVEITEM",NULL);
		} else {
			Local<String> tt = args[0]->ToString();
			String::Utf8Value str(tt);
			IupSetAttribute(cb->hwnd,"REMOVEITEM",*str);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IComboBox::_getCount(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	int nRet = IupGetInt(cb->hwnd,"COUNT");
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IComboBox::_getItemString(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IComboBox* cb = ObjectWrap::Unwrap<IComboBox>(args.Holder());
	if (args.Length()==1 && (args[0]->IsNumber() || args[0]->IsString())) {
		Local<String> tt = args[0]->ToString();
		String::Utf8Value str(tt);
		char* sRet = IupGetAttribute(cb->hwnd,*str);
		if (sRet==NULL) {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
		} else {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, sRet));
		}
	} else {
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, ""));
	}
}

}
