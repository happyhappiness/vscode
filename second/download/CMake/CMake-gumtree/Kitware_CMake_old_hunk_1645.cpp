      }

    if(format == cmSystemTools::FORTRAN_FILE_FORMAT )

      {

      const char* fflags = mf->GetDefinition("CMAKE_FORTRAN_FLAGS");

      fprintf(fout, "SET(CMAKE_FORTRAN_FLAGS \"${CMAKE_FORTRAN_FLAGS} ");

      if(fflags)

        {

        fprintf(fout, " %s ", fflags);
