#include "image.h"
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

IImage::IImage()
{
	hwnd = NULL;
}
IImage::~IImage() {}

void IImage::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IImage"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setImageName", _setImageName);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getChannels", _getChannels);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getWidth", _getWidth);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getHeight", _getHeight);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IImage"),tpl->GetFunction());
}

void IImage::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IImage* obj = new IImage();
	// Create Image
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		obj->hwnd = IupLoadImage(*str);
	}
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IImage::_setImageName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IImage* im = ObjectWrap::Unwrap<IImage>(args.Holder());
	if (im != NULL) {
		if (args.Length()==1 && args[0]->IsString()) {
			Local<String> tt = Local<String>::Cast(args[0]);
			String::Utf8Value str(tt);
			if (im->hwnd != NULL)
			{
				IupSetHandle(*str,im->hwnd);
			}
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IImage::_getChannels(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int nRet = 0;
	IImage* im = ObjectWrap::Unwrap<IImage>(args.Holder());
	if (im != NULL) {
		char* sRet = IupGetAttribute(im->hwnd,"CHANNELS");
		nRet = atoi(sRet);
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IImage::_getWidth(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int nRet = 0;
	IImage* im = ObjectWrap::Unwrap<IImage>(args.Holder());
	if (im != NULL) {
		char* sRet = IupGetAttribute(im->hwnd,"WIDTH");
		nRet = atoi(sRet);
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IImage::_getHeight(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IImage* im = ObjectWrap::Unwrap<IImage>(args.Holder());
	int nRet = 0;
	if (im != NULL) {
		char* sRet = IupGetAttribute(im->hwnd,"HEIGHT");
		nRet = atoi(sRet);
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IImage::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IImage* im = ObjectWrap::Unwrap<IImage>(args.Holder());
	if (im != NULL) {
		if (im->hwnd != NULL) {
			IupDestroy(im->hwnd);
			im->hwnd = NULL;
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
