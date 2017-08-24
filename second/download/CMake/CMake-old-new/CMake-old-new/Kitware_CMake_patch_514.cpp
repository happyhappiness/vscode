@@ -84,7 +84,8 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
     std::string sourceListValue;
     
     // was the list already populated
-    const char *def = this->Makefile->GetDefinition(this->SourceList.c_str());  
+    const char *def =
+      this->Makefile->GetDefinition(this->SourceList.c_str());  
     if (def)
       {
       sourceListValue = def;
@@ -114,7 +115,8 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
         std::string srcName = cmSystemTools::GetFilenameWithoutExtension(*j);
         std::string newName = srcName + "Tcl";
         std::string hname = srcDir + "/" + srcName + ".h";
-        file.SetName(newName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
+        file.SetName(newName.c_str(),
+                     this->Makefile->GetCurrentOutputDirectory(),
                      "cxx",false);
         this->WrapHeaders.push_back(hname);
         // add starting depends
@@ -130,10 +132,12 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
     std::string newName = this->LibraryName;
     newName += "Init";
     this->CreateInitFile(res);
-    cfile.SetName(newName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
+    cfile.SetName(newName.c_str(),
+                  this->Makefile->GetCurrentOutputDirectory(),
                   "cxx",false);
     this->Makefile->AddSource(cfile);
-    this->Makefile->AddDefinition(this->SourceList.c_str(), sourceListValue.c_str());  
+    this->Makefile->AddDefinition(this->SourceList.c_str(),
+                                  sourceListValue.c_str());  
     }
   
   return true;
@@ -144,7 +148,8 @@ void cmVTKWrapTclCommand::FinalPass()
   // first we add the rules for all the .h to Tcl.cxx files
   size_t lastClass = this->WrapClasses.size();
   std::vector<std::string> depends;
-  const char* wtcl = this->Makefile->GetRequiredDefinition("VTK_WRAP_TCL_EXE");
+  const char* wtcl =
+    this->Makefile->GetRequiredDefinition("VTK_WRAP_TCL_EXE");
   const char* hints = this->Makefile->GetDefinition("VTK_WRAP_HINTS");
 
   // wrap all the .h files
@@ -247,17 +252,22 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   fprintf(fout,
           "extern \"C\"\n"
           "{\n"
-          "#if (TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4) && (TCL_RELEASE_LEVEL >= TCL_FINAL_RELEASE)\n"
-          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, CONST84 char *[]);\n"
+          "#if (TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4) "
+          "&& (TCL_RELEASE_LEVEL >= TCL_FINAL_RELEASE)\n"
+          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,"
+          "int, CONST84 char *[]);\n"
           "#else\n"
-          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, char *[]);\n"
+          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,"
+          "int, char *[]);\n"
           "#endif\n"
           "}\n"
           "\n");
 
   for (i = 0; i < classes.size(); i++)
     {
-    fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n             int argc, char *argv[]);\n",classes[i].c_str());
+    fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n"
+            ,classes[i].c_str());
+    fprintf(fout,"             int argc, char *argv[]);\n");
     fprintf(fout,"ClientData %sNewCommand();\n",classes[i].c_str());
     }
   
@@ -280,32 +290,37 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"extern Tcl_HashTable vtkCommandLookup;\n");
     }
   fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  
-  fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp, ClientData arg);\n");
+  fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp,"
+          "ClientData arg);\n");
 
   for (i = 0; i < this->Commands.size(); i++)
     {
-    fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
+    fprintf(fout,
+            "\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
             capcommands[i].c_str());
     }
   
-  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n",
-          kitName);
-  fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
-          kitName);
+  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT "
+          "%s_SafeInit(Tcl_Interp *interp);}\n", kitName);
+  fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init"
+          "(Tcl_Interp *interp);}\n", kitName);
   
   /* create an extern ref to the generic delete function */
   fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");
 
   if (!strcmp(kitName,"Vtkcommontcl"))
     {
-    fprintf(fout,"extern \"C\"\n{\nvoid vtkCommonDeleteAssocData(ClientData cd)\n");
+    fprintf(fout,"extern \"C\"\n{\nvoid "
+            "vtkCommonDeleteAssocData(ClientData cd)\n");
     fprintf(fout,"  {\n");
-    fprintf(fout,"  vtkTclInterpStruct *tis = static_cast<vtkTclInterpStruct*>(cd);\n");
+    fprintf(fout,"  vtkTclInterpStruct *tis = "
+            "static_cast<vtkTclInterpStruct*>(cd);\n");
     fprintf(fout,"  delete tis;\n  }\n}\n");
     }
     
   /* the main declaration */
-  fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);
+  fprintf(fout,
+          "\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);
   fprintf(fout,"  return %s_Init(interp);\n}\n",kitName);
   
   fprintf(fout,"\n\nint VTK_EXPORT %s_Init(Tcl_Interp *interp)\n{\n",
@@ -324,15 +339,17 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
             "  Tcl_InitHashTable(&info->PointerLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
             "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
-    fprintf(fout,
-            "  Tcl_SetAssocData(interp,(char *) \"vtk\",NULL,(ClientData *)info);\n");
-    fprintf(fout,
-            "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData,(ClientData *)info);\n");
+    fprintf(fout, "  Tcl_SetAssocData(interp,(char *) "
+            "\"vtk\",NULL,(ClientData *)info);\n");
+    fprintf(fout, "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData"
+            ",(ClientData *)info);\n");
 
     /* create special vtkCommand command */
-    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
-                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommandForward),\n"
-                 "                    (ClientData *)NULL, NULL);\n\n");
+    fprintf(fout,
+            "  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
+            "                    reinterpret_cast<vtkTclCommandType>("
+            "vtkCommandForward),\n"
+            "                    (ClientData *)NULL, NULL);\n\n");
     }
   
   for (i = 0; i < this->Commands.size(); i++)