#ifndef IUP_MESSAGEDLG_H
#define IUP_MESSAGEDLG_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {

class IMessageDlg : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

protected:
	IMessageDlg();
	~IMessageDlg();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _popup(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _getValue(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}

#endif
