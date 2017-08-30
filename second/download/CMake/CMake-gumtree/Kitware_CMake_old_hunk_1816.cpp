
    /* create special vtkCommand command */
    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommand),\n"
                 "                    (ClientData *)NULL, NULL);\n\n");
    }
  