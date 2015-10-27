#ifndef IUP_DIALOG_H
#define IUP_DIALOG_H

#include <iup.h>
#include "coreobject.h"

namespace iupnode {
	
class IDialog : public CoreObject {
public:
	static void Init(v8::Local<v8::Object> exports);

	Ihandle* hBox;
	int nWidth;
	int nHeight;

protected:
	IDialog();
	~IDialog();
	
	static void _init(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _show(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTitle(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setResizeCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setCloseCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setShowCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setButtonActionCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTextValueChangedCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setListDblClickCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setListValueChangedCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTreeSelectionCB(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void _setTreeExecuteLeafCB(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void _redraw(const v8::FunctionCallbackInfo<v8::Value>& args);

	static void _destroy(const v8::FunctionCallbackInfo<v8::Value>& args);

};

}



#endif