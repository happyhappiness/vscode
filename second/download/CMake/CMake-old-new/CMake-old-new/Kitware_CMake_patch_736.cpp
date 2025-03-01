@@ -228,6 +228,9 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     }
   
   fprintf(fout,"#include \"vtkTclUtil.h\"\n");
+  fprintf(fout,"#include \"vtkVersion.h\"\n");
+  fprintf(fout,"#define VTK_TCL_TO_STRING(x) VTK_TCL_TO_STRING0(x)\n");
+  fprintf(fout,"#define VTK_TCL_TO_STRING0(x) #x\n");
   
   fprintf(fout,
           "extern \"C\"\n"
@@ -333,6 +336,10 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"                  %sCommand);\n",classes[i].c_str());
     }
   
+  fprintf(fout,"  Tcl_PkgProvide(interp, \"%s\", "
+               "VTK_TCL_TO_STRING(VTK_MAJOR_VERSION) \".\" "
+               "VTK_TCL_TO_STRING(VTK_MINOR_VERSION));\n",
+          m_LibraryName.c_str());
   fprintf(fout,"  return TCL_OK;\n}\n");
   fclose(fout);
 