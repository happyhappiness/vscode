  

  fprintf(fout,"\n\nint VTK_EXPORT %s_Init(Tcl_Interp *interp)\n{\n",

          kitName);

  if (!strcmp(kitName,"Vtkcommontcl"))

    {

    fprintf(fout,

	    "  vtkTclInterpStruct *info = new vtkTclInterpStruct;\n");
