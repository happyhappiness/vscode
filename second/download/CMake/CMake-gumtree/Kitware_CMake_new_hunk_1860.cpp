    }

  fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  

  fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp, ClientData arg);\n");



  for (i = 0; i < m_Commands.size(); i++)

    {

    fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",

            capcommands[i].c_str());

    }

  

  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n",

	  kitName);

  fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",

	  kitName);

  

  /* create an extern ref to the generic delete function */

  fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");



  /* the main declaration */

  fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);

