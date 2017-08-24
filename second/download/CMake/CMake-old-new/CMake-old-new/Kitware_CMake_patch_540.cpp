@@ -17,7 +17,8 @@
 #include "cmVTKWrapPythonCommand.h"
 
 // cmVTKWrapPythonCommand
-bool cmVTKWrapPythonCommand::InitialPass(std::vector<std::string> const& argsIn)
+bool cmVTKWrapPythonCommand::InitialPass(std::vector<std::string> const&
+                                         argsIn)
 {
   if(argsIn.size() < 3 )
     {
@@ -102,7 +103,8 @@ void cmVTKWrapPythonCommand::FinalPass()
   // first we add the rules for all the .h to Python.cxx files
   size_t lastClass = m_WrapClasses.size();
   std::vector<std::string> depends;
-  const char* wpython = m_Makefile->GetRequiredDefinition("VTK_WRAP_PYTHON_EXE");
+  const char* wpython = m_Makefile->
+    GetRequiredDefinition("VTK_WRAP_PYTHON_EXE");
   const char* hints = m_Makefile->GetDefinition("VTK_WRAP_HINTS");
 
   // wrap all the .h files
@@ -124,7 +126,8 @@ void cmVTKWrapPythonCommand::FinalPass()
       {
       commandLine.push_back(hints);
       }
-    commandLine.push_back((m_WrapClasses[classNum].GetPropertyAsBool("ABSTRACT") ? "0" : "1"));
+    commandLine.push_back(
+      (m_WrapClasses[classNum].GetPropertyAsBool("ABSTRACT") ? "0" : "1"));
     commandLine.push_back(res);
 
     cmCustomCommandLines commandLines;
@@ -193,9 +196,11 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
   for (i = 0; i < classes.size(); i++)
     {
 #ifdef _WIN32
-    fprintf(fout,"extern  \"C\" {__declspec( dllexport) PyObject *PyVTKClass_%sNew(char *); }\n",classes[i].c_str());
+    fprintf(fout,
+            "extern  \"C\" {__declspec( dllexport) PyObject *PyVTKClass_%sNew(char *); }\n",classes[i].c_str());
 #else
-    fprintf(fout,"extern  \"C\" {PyObject *PyVTKClass_%sNew(char *); }\n",classes[i].c_str());
+    fprintf(fout,"extern  \"C\" {PyObject *PyVTKClass_%sNew(char *); }\n",
+            classes[i].c_str());
 #endif
     }
 
@@ -204,7 +209,8 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
   fprintf(fout,"{NULL, NULL, 0, NULL}};\n\n");
   
 #ifdef _WIN32
-  fprintf(fout,"extern  \"C\" {__declspec( dllexport) void init%s();}\n\n",kitName);
+  fprintf(fout,"extern  \"C\" {__declspec( dllexport) void init%s();}\n\n",
+          kitName);
   fprintf(fout,"void init%s()\n{\n",kitName);
 #else
   fprintf(fout,"extern  \"C\" {void initlib%s();}\n\n",kitName);