      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE CXX)\n");      
      }
    else if ( format == cmSystemTools::FORTRAN_FILE_FORMAT )
      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE FORTRAN)\n");      
      }
    else
      {
      cmSystemTools::Error("Unknown file format for file: ", source.c_str(), 
                           "; TRY_COMPILE only works for C, CXX, and FORTRAN files");
      return -1;
      }
    const char* cflags = mf->GetDefinition("CMAKE_C_FLAGS"); 
