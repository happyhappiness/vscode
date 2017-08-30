    }

  fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  

  fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp, ClientData arg);\n");

  

  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n\n",

	  kitName);

  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n\n",

	  kitName);

  

  /* create an extern ref to the generic delete function */

  fprintf(fout,"\n\nextern void vtkTclGenericDeleteObject(ClientData cd);\n\n");



  /* the main declaration */

  fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);

