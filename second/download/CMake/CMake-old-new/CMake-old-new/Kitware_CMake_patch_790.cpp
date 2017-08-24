@@ -196,7 +196,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"ClientData %sNewCommand();\n",classes[i].c_str());
     }
   
-  if (!strcmp(kitName,"Vtkcommon"))
+  if (!strcmp(kitName,"Vtkcommontcl"))
     {
     fprintf(fout,"int vtkCommand(ClientData cd, Tcl_Interp *interp,\n             int argc, char *argv[]);\n");
     fprintf(fout,"\nTcl_HashTable vtkInstanceLookup;\n");
@@ -226,7 +226,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   
   fprintf(fout,"\n\nint VTK_EXPORT %s_Init(Tcl_Interp *interp)\n{\n",
           kitName);
-  if (!strcmp(kitName,"Vtkcommon"))
+  if (!strcmp(kitName,"Vtkcommontcl"))
     {
     fprintf(fout,
 	    "  vtkTclInterpStruct *info = new vtkTclInterpStruct;\n");