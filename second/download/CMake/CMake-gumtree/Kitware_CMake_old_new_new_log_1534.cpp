fprintf(fout,"int vtkCommandForward(ClientData cd, Tcl_Interp *interp,\n"
                 "                      int argc, char *argv[]){\n"
                 "  return vtkCommand(cd, interp, argc, argv);\n"
                 "}\n");