#include "canvas.h"
#include "eventhandle.h"
#include "bitmap.h"
#include <stdio.h>
#include <string.h>

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Undefined;
using v8::FunctionTemplate;
using v8::Persistent;
using v8::Function;

ICanvas::ICanvas()
{
	hwnd = NULL;
	cdcv = NULL;
}
ICanvas::~ICanvas() {}

void ICanvas::Init(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
	
	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
	tpl->SetClassName(String::NewFromUtf8(isolate, "ICanvas"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	NODE_SET_PROTOTYPE_METHOD(tpl, "init", _init);
	NODE_SET_PROTOTYPE_METHOD(tpl, "createCDCanvas", _createCDCanvas);
	NODE_SET_PROTOTYPE_METHOD(tpl, "clear", _clear);
	NODE_SET_PROTOTYPE_METHOD(tpl, "foreground", _foreground);
	NODE_SET_PROTOTYPE_METHOD(tpl, "background", _background);
	NODE_SET_PROTOTYPE_METHOD(tpl, "lineStyle", _lineStyle);
	NODE_SET_PROTOTYPE_METHOD(tpl, "lineWidth", _lineWidth);
	NODE_SET_PROTOTYPE_METHOD(tpl, "line", _line);
	NODE_SET_PROTOTYPE_METHOD(tpl, "rect", _rect);
	NODE_SET_PROTOTYPE_METHOD(tpl, "arc", _arc);
	NODE_SET_PROTOTYPE_METHOD(tpl, "box", _box);
	NODE_SET_PROTOTYPE_METHOD(tpl, "sector", _sector);
	NODE_SET_PROTOTYPE_METHOD(tpl, "chord", _chord);
	NODE_SET_PROTOTYPE_METHOD(tpl, "font", _font);
	NODE_SET_PROTOTYPE_METHOD(tpl, "text", _text);
	NODE_SET_PROTOTYPE_METHOD(tpl, "putBitmap", _putBitmap);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setDrawCB", _setDrawCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setMotionCB", _setMotionCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "setKeyPressCB", _setKeyPressCB);
	NODE_SET_PROTOTYPE_METHOD(tpl, "redraw", _redraw);
	NODE_SET_PROTOTYPE_METHOD(tpl, "destroy", _destroy);
	
	NODE_SET_METHOD(tpl, "extend", extend);

	constructor.Reset(isolate, tpl->GetFunction());
	exports->Set(String::NewFromUtf8(isolate, "ICanvas"),tpl->GetFunction());
}

void ICanvas::_init(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* obj = new ICanvas();
	// Create canvas
	obj->hwnd = IupCanvas(NULL);
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
	}	obj->Wrap(args.This());
	args.GetReturnValue().Set(Undefined(isolate));
}

/* must be call after map(dialig show) */
void ICanvas::_createCDCanvas(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	cv->cdcv = cdCreateCanvas(CD_IUP,cv->hwnd);
	if (cv->cdcv != NULL) {
		if (cdCanvasActivate(cv->cdcv) == CD_ERROR) {
			printf("cdActivate error\n");
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ICanvas::_clear(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (cv != NULL && cv->cdcv != NULL) {
		cdCanvasClear(cv->cdcv);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_foreground(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber()) {
		int rr = args[0]->Int32Value();
		if (rr>255) rr = rr % 256;
		int gg = args[1]->Int32Value();
		if (gg>255) gg = gg % 256;
		int bb = args[2]->Int32Value();
		if (bb>255) bb = bb % 256;
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			long clr = cdEncodeColor((unsigned char)rr,(unsigned char)gg,(unsigned char)bb);
			cdCanvasForeground(cv->cdcv,clr);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));	
}

void ICanvas::_background(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber()) {
		int rr = args[0]->Int32Value();
		if (rr>255) rr = rr % 256;
		int gg = args[1]->Int32Value();
		if (gg>255) gg = gg % 256;
		int bb = args[2]->Int32Value();
		if (bb>255) bb = bb % 256;
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			long clr = cdEncodeColor((unsigned char)rr,(unsigned char)gg,(unsigned char)bb);
			cdCanvasBackground(cv->cdcv,clr);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));		
}

void ICanvas::_lineStyle(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==1 && args[0]->IsNumber()) {
		int ww = args[0]->Int32Value();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			switch (ww) {
				case 0:
				cdCanvasLineStyle(cv->cdcv,CD_CONTINUOUS);
				break;
				case 1:
				cdCanvasLineStyle(cv->cdcv,CD_DASHED);
				break;
				case 2:
				cdCanvasLineStyle(cv->cdcv,CD_DOTTED);
				break;
				case 3:
				cdCanvasLineStyle(cv->cdcv,CD_DASH_DOT);
				break;
				case 4:
				cdCanvasLineStyle(cv->cdcv,CD_DASH_DOT_DOT);
				break;
				default:
				cdCanvasLineStyle(cv->cdcv,CD_CONTINUOUS);
				break;
			}
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_lineWidth(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==1 && args[0]->IsNumber()) {
		int ww = args[0]->Int32Value();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasLineWidth(cv->cdcv,ww);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_line(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber()) {
		int x1 = args[0]->Int32Value();
		int y1 = args[1]->Int32Value();
		int x2 = args[2]->Int32Value();
		int y2 = args[3]->Int32Value();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasLine(cv->cdcv,x1,y1,x2,y2);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_rect(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber()) {
		int xmin = args[0]->Int32Value();
		int xmax = args[1]->Int32Value();
		int ymin = args[2]->Int32Value();
		int ymax = args[3]->Int32Value();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasRect(cv->cdcv,xmin,xmax,ymin,ymax);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_arc(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==6 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber() && args[5]->IsNumber()) {
		int xc = args[0]->Int32Value();
		int yc = args[1]->Int32Value();
		int ww = args[2]->Int32Value();
		int hh = args[3]->Int32Value();
		double angle1 = args[4]->NumberValue();
		double angle2 = args[5]->NumberValue();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasArc(cv->cdcv,xc,yc,ww,hh,angle1,angle2);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_box(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==4 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber()) {
		int xmin = args[0]->Int32Value();
		int xmax = args[1]->Int32Value();
		int ymin = args[2]->Int32Value();
		int ymax = args[3]->Int32Value();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasBox(cv->cdcv,xmin,xmax,ymin,ymax);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_sector(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==6 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber() && args[5]->IsNumber()) {
		int xc = args[0]->Int32Value();
		int yc = args[1]->Int32Value();
		int ww = args[2]->Int32Value();
		int hh = args[3]->Int32Value();
		double angle1 = args[4]->NumberValue();
		double angle2 = args[5]->NumberValue();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasSector(cv->cdcv,xc,yc,ww,hh,angle1,angle2);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_chord(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==6 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber() && args[5]->IsNumber()) {
		int xc = args[0]->Int32Value();
		int yc = args[1]->Int32Value();
		int ww = args[2]->Int32Value();
		int hh = args[3]->Int32Value();
		double angle1 = args[4]->NumberValue();
		double angle2 = args[5]->NumberValue();
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			cdCanvasChord(cv->cdcv,xc,yc,ww,hh,angle1,angle2);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_font(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==3 && args[0]->IsString() && args[1]->IsNumber() && args[2]->IsNumber()) {
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			char* tf = NULL;
			Local<String> tt = Local<String>::Cast(args[0]);
			int nLen = tt->Utf8Length();
			if (nLen>0) {
				tf = new char[nLen+1];
				memset(tf,0,nLen+1);
				tt->WriteUtf8(tf);
			}
			int st = args[1]->Int32Value();
			switch(st) {
				case 1:
				st = CD_PLAIN;
				break;
				case 2:
				st = CD_BOLD;
				break;
				case 3:
				st = CD_ITALIC;
				break;
				case 4:
				st = CD_UNDERLINE;
				break;
				case 5:
				st = CD_STRIKEOUT;
				break;
				default:
				st = -1;
				break;
			}
			int si = args[2]->Int32Value();
			cdCanvasFont(cv->cdcv,tf,st,si);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_text(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsString()) {
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		if (cv != NULL && cv->cdcv != NULL) {
			int xx = args[0]->Int32Value();
			int yy = args[1]->Int32Value();
			Local<String> tt = args[2]->ToString();
			String::Utf8Value str(tt);
			cdCanvasText(cv->cdcv,xx,yy,*str);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_putBitmap(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length()==5 && args[0]->IsObject() && args[1]->IsNumber() && args[2]->IsNumber() && args[3]->IsNumber() && args[4]->IsNumber()) {
		ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
		Local<Object> xx = Local<Object>::Cast(args[0]);
		IBitmap* ibmp = ObjectWrap::Unwrap<IBitmap>(xx);		
		if (cv != NULL && cv->cdcv !=NULL  && ibmp->bmp != NULL) {
			int xx = args[1]->Int32Value();
			int yy = args[2]->Int32Value();
			int ww = args[3]->Int32Value();
			int hh = args[4]->Int32Value();
			cdCanvasPutBitmap(cv->cdcv,ibmp->bmp,xx,yy,ww,hh);
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_setDrawCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(cv->hwnd,EVT_CANVAS_ACTION,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_setMotionCB(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(cv->hwnd,EVT_CANVAS_MOTION,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_setKeyPressCB(const v8::FunctionCallbackInfo<v8::Value>& args){
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (args.Length()==1 && args[0]->IsFunction()) {
		Persistent<Function> *func;
		Persistent<Object> *caller;
		caller = new Persistent<Object>(isolate,args.Holder());
		Local<Function> fn = Local<Function>::Cast(args[0]);
		func = new Persistent<Function>(isolate,fn);
		SetCommonCallBack(cv->hwnd,EVT_CANVAS_KEYPRESS,caller,func);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_redraw(const v8::FunctionCallbackInfo<v8::Value>& args) {
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (cv != NULL) {
		IupRedraw(cv->hwnd,1);
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

void ICanvas::_destroy(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Isolate* isolate = args.GetIsolate();
	ICanvas* cv = ObjectWrap::Unwrap<ICanvas>(args.Holder());
	if (cv != NULL) {
		if (cv->cdcv != NULL)
		{
			cdKillCanvas(cv->cdcv);
			cv->cdcv = NULL;
		}
		if (cv->hwnd != NULL) {
			IupDestroy(cv->hwnd);
			cv->hwnd = NULL;
		}
	}
	args.GetReturnValue().Set(Undefined(isolate));
}

}
