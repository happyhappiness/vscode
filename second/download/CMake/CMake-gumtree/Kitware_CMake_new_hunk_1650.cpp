        }

      fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");

      }

    if(format == cmSystemTools::FORTRAN_FILE_FORMAT )

      {

      const char* fflags = mf->GetDefinition("CMAKE_FORTRAN_FLAGS");

      fprintf(fout, "SET(CMAKE_FORTRAN_FLAGS \"${CMAKE_FORTRAN_FLAGS} ");

      if(fflags)

        {

        fprintf(fout, " %s ", fflags);

        }

      fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");

      }

    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");

    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");

    // handle any compile flags we need to pass on
