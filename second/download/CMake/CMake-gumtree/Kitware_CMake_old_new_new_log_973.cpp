fprintf(fout,
          "extern \"C\"\n"
          "{\n"
          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, char *[]);\n"
          "}\n"
          "\n");