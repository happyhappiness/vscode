            "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData,(ClientData *)info);\n");



    /* create special vtkCommand command */

    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"

                 "                    reinterpret_cast<vtkTclCommandType>(vtkCommand),\n"

                 "                    (ClientData *)NULL, NULL);\n\n");

    }

  

  for (i = 0; i < m_Commands.size(); i++)
