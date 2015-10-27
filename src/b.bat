del *.node
del *.obj
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include /I..\deps\cd5.9\include iupnode.cpp
cl /c /EHsc /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include eventhandle.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include coreobject.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include iupapp.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include dialog.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include label.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include button.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include text.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include multiline.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include list.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include combobox.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include tree.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include image.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include /I..\deps\cd5.9\include canvas.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include /I..\deps\cd5.9\include bitmap.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include filedlg.cpp
cl /c /I..\deps\node-v4.2.1\include\node /I..\deps\iup3.16\include messagedlg.cpp
link /DLL /RELEASE /OUT:iupnode.node /LIBPATH:..\deps\node-v4.2.1\lib /LIBPATH:..\deps\iup3.16 /LIBPATH:..\deps\im3.10 /LIBPATH:..\deps\cd5.9 node.lib iup.lib iupim.lib im.lib iupcd.lib cd.lib freetype6.lib zlib1.lib kernel32.lib user32.lib gdi32.lib shell32.lib comdlg32.lib advapi32.lib comctl32.lib uuid.lib oleaut32.lib ole32.lib iupnode.obj eventhandle.obj coreobject.obj iupapp.obj dialog.obj label.obj button.obj text.obj multiline.obj list.obj combobox.obj tree.obj image.obj canvas.obj bitmap.obj filedlg.obj messagedlg.obj

