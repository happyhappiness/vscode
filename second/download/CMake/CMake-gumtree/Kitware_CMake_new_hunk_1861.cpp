    fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",vtkCommand,\n		    (ClientData *)NULL, NULL);\n\n");
    }
  
  for (i = 0; i < m_Commands.size(); i++)
    {
    fprintf(fout,"  %s_Init(interp);\n", capcommands[i].c_str());
    }
  fprintf(fout,"\n");

  for (i = 0; i < classes.size(); i++)
    {
    fprintf(fout,"  vtkTclCreateNew(interp,(char *) \"%s\", %sNewCommand,\n",