@@ -157,7 +157,10 @@ void cmVTKWrapTclCommand::FinalPass()
   
   // wrap all the .h files
   depends.push_back(wtcl);
-  depends.push_back(hints);
+  if (strcmp("${VTK_WRAP_HINTS}",hints.c_str()))
+    {
+    depends.push_back(hints);
+    }
   for(int classNum = 0; classNum < lastClass; classNum++)
     {
     m_Makefile->AddSource(m_WrapClasses[classNum],m_SourceList.c_str());
@@ -270,7 +273,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
 
   if (!strcmp(kitName,"Vtkcommontcl"))
     {
-    fprintf(fout,"void vtkCommonDeleteAssocData(ClientData cd, Tcl_Interp *)\n");
+    fprintf(fout,"void vtkCommonDeleteAssocData(ClientData cd)\n");
     fprintf(fout,"  {\n");
     fprintf(fout,"  vtkTclInterpStruct *tis = static_cast<vtkTclInterpStruct*>(cd);\n");
     fprintf(fout,"  delete tis;\n  }\n");
@@ -297,7 +300,9 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,
 	    "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
-            "  Tcl_SetAssocData(interp,(char *) \"vtk\",vtkCommonDeleteAssocData,(ClientData *)info);\n");
+            "  Tcl_SetAssocData(interp,(char *) \"vtk\",NULL,(ClientData *)info);\n");
+    fprintf(fout,
+            "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData,(ClientData *)info);\n");
 
     /* create special vtkCommand command */
     fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",vtkCommand,\n		    (ClientData *)NULL, NULL);\n\n");