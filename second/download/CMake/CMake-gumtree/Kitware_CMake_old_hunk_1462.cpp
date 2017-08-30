  fprintf(fout,

          "extern \"C\"\n"

          "{\n"

          "#if (TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4) && (TCL_RELEASE_LEVEL >= TCL_FINAL_RELEASE)\n"

          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, CONST84 char *[]);\n"

          "#else\n"

          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,int, char *[]);\n"

          "#endif\n"

          "}\n"

          "\n");



  for (i = 0; i < classes.size(); i++)

    {

    fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n             int argc, char *argv[]);\n",classes[i].c_str());

    fprintf(fout,"ClientData %sNewCommand();\n",classes[i].c_str());

    }

  

