
  if (!strcmp(kitName,"Vtkcommontcl"))
    {
    fprintf(fout,"void vtkCommonDeleteAssocData(ClientData cd, Tcl_Interp *)\n");
    fprintf(fout,"  {\n");
    fprintf(fout,"  vtkTclInterpStruct *tis = static_cast<vtkTclInterpStruct*>(cd);\n");
    fprintf(fout,"  delete tis;\n  }\n");
