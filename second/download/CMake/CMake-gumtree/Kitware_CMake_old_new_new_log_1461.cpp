f(fout,"  Tcl_PkgProvide(interp, \"%s\", "
               "VTK_TCL_TO_STRING(VTK_MAJOR_VERSION) \".\" "
               "VTK_TCL_TO_STRING(VTK_MINOR_VERSION));\n",
          m_LibraryName.c_str());