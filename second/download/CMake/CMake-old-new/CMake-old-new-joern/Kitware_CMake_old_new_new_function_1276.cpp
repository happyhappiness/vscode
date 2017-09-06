bool cmVTKWrapTclCommand::WriteInit(const char *kitName, 
                                    std::string& outFileName,
                                    std::vector<std::string>& classes)
{
  unsigned int i;
  std::string tempOutputFile = outFileName + ".tmp";
  FILE *fout = fopen(tempOutputFile.c_str(),"w");
  if (!fout)
    {
    cmSystemTools::Error("Failed to open TclInit file for ",
                         tempOutputFile.c_str());
    cmSystemTools::ReportLastSystemError("");
    return false;
    }

  // capitalized commands just once
  std::vector<std::string> capcommands;
  for (i = 0; i < this->Commands.size(); i++)
    {
    capcommands.push_back(cmSystemTools::Capitalized(this->Commands[i]));
    }
  
  fprintf(fout,"#include \"vtkTclUtil.h\"\n");
  fprintf(fout,"#include \"vtkVersion.h\"\n");
  fprintf(fout,"#define VTK_TCL_TO_STRING(x) VTK_TCL_TO_STRING0(x)\n");
  fprintf(fout,"#define VTK_TCL_TO_STRING0(x) #x\n");
  
  fprintf(fout,
          "extern \"C\"\n"
          "{\n"
          "#if (TCL_MAJOR_VERSION == 8) && (TCL_MINOR_VERSION >= 4) "
          "&& (TCL_RELEASE_LEVEL >= TCL_FINAL_RELEASE)\n"
          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,"
          "int, CONST84 char *[]);\n"
          "#else\n"
          "  typedef int (*vtkTclCommandType)(ClientData, Tcl_Interp *,"
          "int, char *[]);\n"
          "#endif\n"
          "}\n"
          "\n");

  for (i = 0; i < classes.size(); i++)
    {
    fprintf(fout,"int %sCommand(ClientData cd, Tcl_Interp *interp,\n"
            ,classes[i].c_str());
    fprintf(fout,"             int argc, char *argv[]);\n");
    fprintf(fout,"ClientData %sNewCommand();\n",classes[i].c_str());
    }
  
  if (!strcmp(kitName,"Vtkcommontcl"))
    {
    fprintf(fout,"int vtkCommand(ClientData cd, Tcl_Interp *interp,\n"
                 "               int argc, char *argv[]);\n");
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
    fprintf(fout,"\nextern Tcl_HashTable vtkInstanceLookup;\n");
    fprintf(fout,"extern Tcl_HashTable vtkPointerLookup;\n");
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
          kitName);
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
    fprintf(fout, "  Tcl_SetAssocData(interp,(char *) "
            "\"vtk\",NULL,(ClientData *)info);\n");
    fprintf(fout, "  Tcl_CreateExitHandler(vtkCommonDeleteAssocData"
            ",(ClientData *)info);\n");

    /* create special vtkCommand command */
    fprintf(fout,
            "  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",\n"
            "                    reinterpret_cast<vtkTclCommandType>("
            "vtkCommandForward),\n"
            "                    (ClientData *)NULL, NULL);\n\n");
    }
  
  for (i = 0; i < this->Commands.size(); i++)
    {
    fprintf(fout,"  %s_Init(interp);\n", capcommands[i].c_str());
    }
  fprintf(fout,"\n");

  for (i = 0; i < classes.size(); i++)
    {
    fprintf(fout,"  vtkTclCreateNew(interp,(char *) \"%s\", %sNewCommand,\n",
            classes[i].c_str(), classes[i].c_str());
    fprintf(fout,"                  %sCommand);\n",classes[i].c_str());
    }
  
  fprintf(fout,"  char pkgName[]=\"%s\";\n", this->LibraryName.c_str());
  fprintf(fout,"  char pkgVers[]=VTK_TCL_TO_STRING(VTK_MAJOR_VERSION)"
               " \".\" "
               "VTK_TCL_TO_STRING(VTK_MINOR_VERSION);\n");
  fprintf(fout,"  Tcl_PkgProvide(interp, pkgName, pkgVers);\n");
  fprintf(fout,"  return TCL_OK;\n}\n");
  fclose(fout);

  // copy the file if different
  cmSystemTools::CopyFileIfDifferent(tempOutputFile.c_str(),
                                     outFileName.c_str());
  cmSystemTools::RemoveFile(tempOutputFile.c_str());

  return true;
}