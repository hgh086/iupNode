#ifndef IUP_CANVAS_H
#define IUP_CANVAS_H

#include <iup.h>
#include <cd.h>
#include <cdiup.h>
#include "coreobject.h"

namespace iupnode {

class ICanvas : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);
	cdCanvas* cdcv;

protected:
	ICanvas();
	~ICanvas();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	static void _createCDCanvas(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _clear(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _foreground(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _background(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _lineStyle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _lineWidth(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _line(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _rect(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _arc(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _box(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _sector(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _chord(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _font(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _text(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _putBitmap(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void _setDrawCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setMotionCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setKeyPressCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	static void _redraw(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	static void _destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
