  if (!strcmp(kitName,"Vtkcommontcl"))

    {

    fprintf(fout,

	    "  vtkTclInterpStruct *info = new vtkTclInterpStruct;\n");

    fprintf(fout,

            "  info->Number = 0; info->InDelete = 0; info->DebugOn = 0;\n");

    fprintf(fout,"\n");

    fprintf(fout,"\n");

    fprintf(fout,

	    "  Tcl_InitHashTable(&info->InstanceLookup, TCL_STRING_KEYS);\n");

    fprintf(fout,

	    "  Tcl_InitHashTable(&info->PointerLookup, TCL_STRING_KEYS);\n");

    fprintf(fout,

	    "  Tcl_InitHashTable(&info->CommandLookup, TCL_STRING_KEYS);\n");

    fprintf(fout,

            "  Tcl_SetAssocData(interp,(char *) \"vtk\",NULL,(ClientData *)info);\n");

    fprintf(fout,

