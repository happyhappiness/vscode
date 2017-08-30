      {

      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE CXX)\n");      

      }

    else

      {

      cmSystemTools::Error("Unknown file format for file: ", source.c_str(), 

                           "; TRY_COMPILE only works for C and CXX files");

      return -1;

      }

    const char* cflags = mf->GetDefinition("CMAKE_C_FLAGS"); 

