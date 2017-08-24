@@ -269,6 +269,14 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   /* create an extern ref to the generic delete function */
   fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");
 
+  if (!strcmp(kitName,"Vtkcommontcl"))
+    {
+    fprintf(fout,"void vtkCommonDeleteAssocData(ClientData cd, Tcl_Interp *)\n");
+    fprintf(fout,"  {\n");
+    fprintf(fout,"  vtkTclInterpStruct *tis = static_cast<vtkTclInterpStruct*>(cd);\n");
+    fprintf(fout,"  delete tis;\n  }\n");
+    }
+    
   /* the main declaration */
   fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);
   fprintf(fout,"  return %s_Init(interp);\n}\n",kitName);
@@ -290,7 +298,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,
 	    "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
     fprintf(fout,
-            "  Tcl_SetAssocData(interp,(char *) \"vtk\",NULL,(ClientData *)info);\n");
+            "  Tcl_SetAssocData(interp,(char *) \"vtk\",vtkCommonDeleteAssocData,(ClientData *)info);\n");
 
     /* create special vtkCommand command */
     fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",vtkCommand,\n		    (ClientData *)NULL, NULL);\n\n");