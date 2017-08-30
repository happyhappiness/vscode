    fprintf(fout,"                  %sCommand);\n",classes[i].c_str());

    }

  

  fprintf(fout,"  char pkgName[]=\"%s\";\n", this->LibraryName.c_str());

  fprintf(fout,"  char pkgVers[]=VTK_TCL_TO_STRING(VTK_MAJOR_VERSION)"

               " \".\" "

               "VTK_TCL_TO_STRING(VTK_MINOR_VERSION);\n");
