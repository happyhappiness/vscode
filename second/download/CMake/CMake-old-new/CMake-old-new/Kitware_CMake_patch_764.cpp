@@ -249,6 +249,10 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"\nTcl_HashTable vtkInstanceLookup;\n");
     fprintf(fout,"Tcl_HashTable vtkPointerLookup;\n");
     fprintf(fout,"Tcl_HashTable vtkCommandLookup;\n");
+    fprintf(fout,"int vtkCommandForward(ClientData cd, Tcl_Interp *interp,\n"
+                 "                      int argc, char *argv[]){\n"
+                 "  return vtkCommand(cd, interp, argc, argv);\n"
+                 "}\n");
     }
   else
     {
@@ -308,7 +312,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
 
     /* create special vtkCommand command */
     fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
-                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommand),\n"
+                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommandForward),\n"
                  "                    (ClientData *)NULL, NULL);\n\n");
     }
   