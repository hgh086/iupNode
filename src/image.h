#ifndef IUP_IMAGE_H
#define IUP_IMAGE_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class IImage : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	IImage();
	~IImage();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setImageName(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getChannels(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getWidth(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getHeight(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
