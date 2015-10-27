#include <node.h>
#include "coreobject.h"
#include "eventhandle.h"
#include "iupapp.h"
#include "dialog.h"
#include "label.h"
#include "button.h"
#include "text.h"
#include "multiline.h"
#include "list.h"
#include "combobox.h"
#include "tree.h"
#include "image.h"
#include "canvas.h"
#include "bitmap.h"
#include "filedlg.h"
#include "messagedlg.h"

namespace iupnode {
using v8::Local;
using v8::Object;
using v8::Isolate;
using v8::String;
using v8::Script;

void LoadGFunction(Local<Object> exports) {
	Isolate* isolate = exports->GetIsolate();
	Local<String> sss = String::NewFromUtf8(isolate,"\
	global.__superWrapMethod = function(origMethod, superMethod) {\
		return function() {\
			var tmp = this._super;\
			this._super = superMethod;\
			var ret = origMethod.apply(this, arguments);\
			this._super = tmp;\
			return ret;\
		};\
	}");
	Local<Script> scr = Script::Compile(sss);
	scr->Run();
}
	
void InitAll(Local<Object> exports) {
	InitEventData();
	LoadGFunction(exports);
	CoreObject::Init(exports);
	IupApp::Init(exports);
	IDialog::Init(exports);
	ILabel::Init(exports);
	IButton::Init(exports);
	IText::Init(exports);
	IMultiLine::Init(exports);
	IList::Init(exports);
	IComboBox::Init(exports);
	ITree::Init(exports);
	IImage::Init(exports);
	ICanvas::Init(exports);
	IBitmap::Init(exports);
	IFileDlg::Init(exports);
	IMessageDlg::Init(exports);
}

NODE_MODULE(iupnode, InitAll)

}
