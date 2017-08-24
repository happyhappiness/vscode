@@ -76,7 +76,8 @@ bool cmVTKWrapPythonCommand::InitialPass(std::vector<std::string> const&
         }
       std::string srcName = cmSystemTools::GetFilenameWithoutExtension(*j);
       std::string newName = srcName + "Python";
-      file.SetName(newName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
+      file.SetName(newName.c_str(), 
+                   this->Makefile->GetCurrentOutputDirectory(),
                    "cxx",false);
       std::string hname = cdir + "/" + srcName + ".h";
       this->WrapHeaders.push_back(hname);
@@ -94,7 +95,8 @@ bool cmVTKWrapPythonCommand::InitialPass(std::vector<std::string> const&
   cfile.SetName(initName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
                 "cxx",false);
   this->Makefile->AddSource(cfile);
-  this->Makefile->AddDefinition(this->SourceList.c_str(), sourceListValue.c_str());
+  this->Makefile->AddDefinition(this->SourceList.c_str(),
+                                sourceListValue.c_str());
   return true;
 }
 
@@ -196,8 +198,8 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
   for (i = 0; i < classes.size(); i++)
     {
 #ifdef _WIN32
-    fprintf(fout,
-            "extern  \"C\" {__declspec( dllexport) PyObject *PyVTKClass_%sNew(char *); }\n",classes[i].c_str());
+    fprintf(fout, "extern  \"C\" {__declspec( dllexport) "
+            "PyObject *PyVTKClass_%sNew(char *); }\n", classes[i].c_str());
 #else
     fprintf(fout,"extern  \"C\" {PyObject *PyVTKClass_%sNew(char *); }\n",
             classes[i].c_str());
@@ -229,16 +231,17 @@ bool cmVTKWrapPythonCommand::WriteInit(const char *kitName,
           kitName);
   
   fprintf(fout,"  d = PyModule_GetDict(m);\n");
-  fprintf(fout,"  if (!d) Py_FatalError(\"can't get dictionary for module %s!\");\n\n",
-          kitName);
+  fprintf(fout,"  if (!d) Py_FatalError"
+          "(\"can't get dictionary for module %s!\");\n\n", kitName);
 
   for (i = 0; i < classes.size(); i++)
     {
     fprintf(fout,"  if ((c = PyVTKClass_%sNew(modulename)))\n",
             classes[i].c_str());
     fprintf(fout,"    if (-1 == PyDict_SetItemString(d, \"%s\", c))\n",
             classes[i].c_str());
-    fprintf(fout,"      Py_FatalError(\"can't add class %s to dictionary!\");\n\n",
+    fprintf(fout,
+            "      Py_FatalError(\"can't add class %s to dictionary!\");\n\n",
             classes[i].c_str());
     }
   fprintf(fout,"}\n\n");