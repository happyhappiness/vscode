fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommandForward),\n"
                 "                    (ClientData *)NULL, NULL);\n\n");