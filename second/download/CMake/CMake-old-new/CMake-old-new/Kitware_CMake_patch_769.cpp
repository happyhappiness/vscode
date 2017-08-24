@@ -229,6 +229,13 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   
   fprintf(fout,"#include \"vtkTclUtil.h\"\n");
   
+  fprintf(fout,
+          "extern \"C\"\n"
+          "{\n"
+          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, char *[]);\n"
+          "}\n"
+          "\n");
+
   for (i = 0; i < classes.size(); i++)
     {
     fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n             int argc, char *argv[]);\n",classes[i].c_str());
@@ -300,7 +307,9 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
             "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData,(ClientData *)info);\n");
 
     /* create special vtkCommand command */
-    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",vtkCommand,\n		    (ClientData *)NULL, NULL);\n\n");
+    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
+                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommand),\n"
+                 "                    (ClientData *)NULL, NULL);\n\n");
     }
   
   for (i = 0; i < m_Commands.size(); i++)