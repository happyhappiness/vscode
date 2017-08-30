    fprintf(fout,"\nTcl_HashTable vtkInstanceLookup;\n");

    fprintf(fout,"Tcl_HashTable vtkPointerLookup;\n");

    fprintf(fout,"Tcl_HashTable vtkCommandLookup;\n");

    fprintf(fout,"int vtkCommandForward(ClientData cd, Tcl_Interp *interp,\n"

                 "                      int argc, char *argv[]){\n"

                 "  return vtkCommand(cd, interp, argc, argv);\n"

                 "}\n");

    }

  else

    {

