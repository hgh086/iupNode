#include "filedlg.h"
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

IFileDlg::IFileDlg()
{
	hwnd = NULL;
}
IFileDlg::~IFileDlg() {}

void IFileDlg::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IFileDlg"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "popup", _popup);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getValue", _getValue);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IFileDlg"),tpl->GetFunction());
}

void IFileDlg::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IFileDlg* obj = new IFileDlg();
	// Create Filedlg
	obj->hwnd = IupFileDlg();
	if (args.Length()>=1 && args[0]->IsNumber()) {
		int ty = args[0]->Int32Value();
		switch(ty) {
			case 1:
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "SAVE");
			break;
			case 2:
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "DIR");
			break;
			default:
			IupSetStrAttribute(obj->hwnd,"DIALOGTYPE", "OPEN");
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
		IupSetStrAttribute(obj->hwnd,"FILTER", *str);
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IFileDlg::_popup(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IFileDlg* ifd = ObjectWrap::Unwrap<IFileDlg>(args.Holder());
	if (ifd != NULL) {
		if (ifd->hwnd != NULL) {
			IupPopup(ifd->hwnd, IUP_CURRENT, IUP_CURRENT); 
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IFileDlg::_getValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IFileDlg* ifd = ObjectWrap::Unwrap<IFileDlg>(args.Holder());
	if (ifd != NULL) {
		if (ifd->hwnd != NULL) {
			if (IupGetInt(ifd->hwnd, "STATUS") == -1) {
				args.GetReturnValue().Set(String::NewFromUtf8(isolate,""));
			} else {
				char* sRet = IupGetAttribute(ifd->hwnd,"VALUE");
				args.GetReturnValue().Set(String::NewFromUtf8(isolate,sRet));
			}
		} else {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate,""));
		}
	} else {
		args.GetReturnValue().Set(String::NewFromUtf8(isolate,""));
	}
}

void IFileDlg::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IFileDlg* ifd = ObjectWrap::Unwrap<IFileDlg>(args.Holder());
	if (ifd != NULL) {
		if (ifd->hwnd != NULL) {
			IupDestroy(ifd->hwnd);
			ifd->hwnd = NULL;
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
