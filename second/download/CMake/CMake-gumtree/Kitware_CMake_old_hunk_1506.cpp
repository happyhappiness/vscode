      }

    

    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());

    fprintf(fout, "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");

    fclose(fout);

    projectName = "CMAKE_TRY_COMPILE";

    targetName = "cmTryCompileExec";

