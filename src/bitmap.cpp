#include "bitmap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iupim.h>
#include <cdiup.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Integer;
using v8::Undefined;
using v8::FunctionTemplate;

IBitmap::IBitmap()
{
	hwnd = NULL;
	bmp = NULL;
	channels = 0;
	width = 0;
	height = 0;
}
IBitmap::~IBitmap() {}

void IBitmap::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
		
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "IBitmap"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "createBitmap", _createBitmap);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getChannels", _getChannels);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getWidth", _getWidth);
	NODE_SET_PROTOTYPE_METHOD(tpl, "getHeight", _getHeight);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "IBitmap"),tpl->GetFunction());
}

void IBitmap::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IBitmap* obj = new IBitmap();
	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

void IBitmap::_createBitmap(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(args.Holder());
	if (args.Length()==1 && args[0]->IsString()) {
		Local<String> tt = Local<String>::Cast(args[0]);
		String::Utf8Value str(tt);
		Ihandle *img = IupLoadImage(*str);
		if (img != NULL)
		{
			ibmp->channels = atoi(IupGetAttribute(img,"CHANNELS"));
			ibmp->width = atoi(IupGetAttribute(img,"WIDTH"));
			ibmp->height = atoi(IupGetAttribute(img,"HEIGHT"));
			unsigned char* d = (unsigned char*)IupGetAttribute(img,"WID");
			if (ibmp->channels==3) {
				ibmp->bmp = cdCreateBitmap(ibmp->width,ibmp->height,CD_RGB);
				unsigned char* pr = cdBitmapGetData(ibmp->bmp,CD_IRED);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pr+i) = *(d+i*3);
				}
				unsigned char* pg = cdBitmapGetData(ibmp->bmp,CD_IGREEN);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pg+i) = *(d+i*3+1);
				}
				unsigned char* pb = cdBitmapGetData(ibmp->bmp,CD_IBLUE);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pb+i) = *(d+i*3+2);
				}
			} else if(ibmp->channels==4)
			{
				ibmp->bmp = cdCreateBitmap(ibmp->width,ibmp->height,CD_RGBA);
				unsigned char* pr = cdBitmapGetData(ibmp->bmp,CD_IRED);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pr+i) = *(d+i*4);
				}
				unsigned char* pg = cdBitmapGetData(ibmp->bmp,CD_IGREEN);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pg+i) = *(d+i*4+1);
				}
				unsigned char* pb = cdBitmapGetData(ibmp->bmp,CD_IBLUE);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pb+i) = *(d+i*4+2);
				}
				unsigned char* pa = cdBitmapGetData(ibmp->bmp,CD_IALPHA);
				for(int i=0;i<ibmp->width*ibmp->height;i++) {
					*(pa+i) = *(d+i*4+3);
				}
			}
			IupDestroy(img);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void IBitmap::_getChannels(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int nRet = 0;
	IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(args.Holder());
	if (ibmp != NULL) {
		nRet = ibmp->channels;
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IBitmap::_getWidth(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int nRet = 0;
	IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(args.Holder());
	if (ibmp != NULL) {
		nRet = ibmp->width;
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IBitmap::_getHeight(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(args.Holder());
	int nRet = 0;
	if (ibmp != NULL) {
		nRet = ibmp->height;
	}
	args.GetReturnValue().Set(Integer::New(isolate,nRet));
}

void IBitmap::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(args.Holder());
	if (ibmp != NULL) {
		if (ibmp->bmp != NULL) {
			cdKillBitmap(ibmp->bmp);
			ibmp->bmp = NULL;
			ibmp->channels = 0;
			ibmp->width = 0;
			ibmp->height = 0;
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
