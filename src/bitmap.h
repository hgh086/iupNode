#ifndef IUP_BITMAP_H
#define IUP_BITMAP_H

#include <iup.h>
#include <cd.h>
#include "coreobject.h"

namespace iupnode {

class IBitmap : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

	cdBitmap* bmp;
	int channels;
	int width;
	int height;
	
protected:
	IBitmap();
	~IBitmap();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _createBitmap(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getChannels(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getWidth(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getHeight(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
