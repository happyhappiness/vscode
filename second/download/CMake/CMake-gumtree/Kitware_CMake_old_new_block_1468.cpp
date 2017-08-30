{
    // remove any CMakeCache.txt files so we will have a clean test
    std::string ccFile = tmpString + "/CMakeCache.txt";
    cmSystemTools::RemoveFile(ccFile.c_str());
    
    // we need to create a directory and CMakeList file etc...
    // first create the directories
    sourceDirectory = binaryDirectory;

    // now create a CMakeList.txt file in that directory
    FILE *fout = fopen(outFileName.c_str(),"w");
    if (!fout)
      {
      cmSystemTools::Error("Failed to create CMakeList file for ", 
                           outFileName.c_str());
      return -1;
      }
    
    std::string source = argv[2];
    cmSystemTools::FileFormat format = 
      cmSystemTools::GetFileFormat( 
        cmSystemTools::GetFilenameExtension(source).c_str());
    if ( format == cmSystemTools::C_FILE_FORMAT )
      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE C)\n");      
      }
    else if ( format == cmSystemTools::CXX_FILE_FORMAT )
      {
      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE CXX)\n");      
      }
    else
      {
      cmSystemTools::Error("Unknown file format for file: ", source.c_str(), 
                           "; TRY_COMPILE only works for C and CXX files");
      return -1;
      }

    fprintf(fout, "SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS})\n");
    fprintf(fout, "SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS})\n");
    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
    // handle any compile flags we need to pass on
    if (compileFlags.size())
      {
      fprintf(fout, "ADD_DEFINITIONS( ");
      for (i = 0; i < compileFlags.size(); ++i)
        {
        fprintf(fout,"%s ",compileFlags[i].c_str());
        }
      fprintf(fout, ")\n");
      }
    
    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());
    fprintf(fout, "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    targetName = "cmTryCompileExec";
    }