#include "messagedlg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iupim.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Integer;
using v8::Undefined;
using v8::FunctionTemplate;

IMessageDlg::IMessageDlg()
{
	hwnd = NULL;
}
IMessageDlg::~IMessageDlg() {}

void IMessageDlg::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IMessageDlg"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "popup", _popup);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", _getValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IMessageDlg"),tpl->GetFunction());
}

void IMessageDlg::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IMessageDlg* obj = new IMessageDlg();
	// Create messagedlg
	obj->hwnd = IupMessageDlg();
	if (args.Length()>=1 && args[0]->IsNumber()) {
		int ty = args[0]->Int32Value();
		switch(ty) {
			case 1:
			IupSetStrAttribute(obj->hwnd,"BUTTONS", "OKCANCEL");
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "QUESTION");
			break;
			case 2:
			IupSetStrAttribute(obj->hwnd,"BUTTONS", "YESNO");
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "QUESTION");
			break;
			default:
			IupSetStrAttribute(obj->hwnd,"BUTTONS", "OK");
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "INFORMATION");
			break;
		}
	}
	if (args.Length()>=2 && args[1]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[1]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"TITLE", *str);
	}
	if (args.Length()>=3 && args[2]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[2]);
		String::Utf8Value str(tt);
		IupSetStrAttribute(obj->hwnd,"VALUE", *str);
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IMessageDlg::_popup(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IMessageDlg* imd = ObjectWrap::Unwrap<IMessageDlg>(args.Holder());
	if (imd != NULL) {
		if (imd->hwnd != NULL) {
			IupPopup(imd->hwnd, IUP_CURRENT, IUP_CURRENT); 
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IMessageDlg::_getValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IMessageDlg* imd = ObjectWrap::Unwrap<IMessageDlg>(args.Holder());
	if (imd != NULL) {
		if (imd->hwnd != NULL) {
			char* sRet = IupGetAttribute(imd->hwnd,"BUTTONRESPONSE");
			args.GetReturnValue().Set(String::NewFromUtf8(isolate,sRet));
		} else {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate,""));
		}
	} else {
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,""));
	}
}

void IMessageDlg::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IMessageDlg* imd = ObjectWrap::Unwrap<IMessageDlg>(args.Holder());
	if (imd != NULL) {
		if (imd->hwnd != NULL) {
			IupDestroy(imd->hwnd);
			imd->hwnd = NULL;
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
