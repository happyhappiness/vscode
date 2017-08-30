      }

    if(format == cmSystemTools::FORTRAN_FILE_FORMAT )

      {

      const char* fflags = mf->GetDefinition("CMAKE_Fortran_FLAGS");

      fprintf(fout, "SET(CMAKE_Fortran_FLAGS \"${CMAKE_Fortran_FLAGS} ");

      if(fflags)

        {

        fprintf(fout, " %s ", fflags);
