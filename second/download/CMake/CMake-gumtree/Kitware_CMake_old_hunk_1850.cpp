  /* create an extern ref to the generic delete function */

  fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");



  /* the main declaration */

  fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);

  fprintf(fout,"  return %s_Init(interp);\n}\n",kitName);

