    fprintf(fout,"extern Tcl_HashTable vtkCommandLookup;\n");

    }

  fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  

  fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp,"

          "ClientData arg);\n");



  for (i = 0; i < this->Commands.size(); i++)

    {

    fprintf(fout,

            "\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",

            capcommands[i].c_str());

    }

  

  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT "

          "%s_SafeInit(Tcl_Interp *interp);}\n", kitName);

  fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init"

          "(Tcl_Interp *interp);}\n", kitName);

  

  /* create an extern ref to the generic delete function */

  fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");



  if (!strcmp(kitName,"Vtkcommontcl"))

    {

    fprintf(fout,"extern \"C\"\n{\nvoid "

            "vtkCommonDeleteAssocData(ClientData cd)\n");

    fprintf(fout,"  {\n");

    fprintf(fout,"  vtkTclInterpStruct *tis = "

            "static_cast<vtkTclInterpStruct*>(cd);\n");

    fprintf(fout,"  delete tis;\n  }\n}\n");

    }

    

  /* the main declaration */

  fprintf(fout,

          "\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);

  fprintf(fout,"  return %s_Init(interp);\n}\n",kitName);

  

  fprintf(fout,"\n\nint VTK_EXPORT %s_Init(Tcl_Interp *interp)\n{\n",

