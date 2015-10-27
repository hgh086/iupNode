#ifndef IUP_LABEL_H
#define IUP_LABEL_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class ILabel : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	ILabel();
	~ILabel();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosx(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setPosy(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTitle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setImage(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
