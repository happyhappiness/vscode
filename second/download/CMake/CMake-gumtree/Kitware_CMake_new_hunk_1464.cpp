            "  Tcl_InitHashTable(&info->PointerLookup, TCL_STRING_KEYS);\n");
    fprintf(fout,
            "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");
    fprintf(fout, "  Tcl_SetAssocData(interp,(char *) "
            "\"vtk\",NULL,(ClientData *)info);\n");
    fprintf(fout, "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData"
            ",(ClientData *)info);\n");

    /* create special vtkCommand command */
    fprintf(fout,
            "  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
            "                    reinterpret_cast<vtkTclCommandType>("
            "vtkCommandForward),\n"
            "                    (ClientData *)NULL, NULL);\n\n");
    }
  
  for (i = 0; i < this->Commands.size(); i++)