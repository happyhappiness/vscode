  /* create an extern ref to the generic delete function */

  fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");



  if (!strcmp(kitName,"Vtkcommontcl"))

    {

    fprintf(fout,"void vtkCommonDeleteAssocData(ClientData cd, Tcl_Interp *)\n");

    fprintf(fout,"  {\n");

    fprintf(fout,"  vtkTclInterpStruct *tis = static_cast<vtkTclInterpStruct*>(cd);\n");

    fprintf(fout,"  delete tis;\n  }\n");

    }

    

  /* the main declaration */

  fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);

  fprintf(fout,"  return %s_Init(interp);\n}\n",kitName);

