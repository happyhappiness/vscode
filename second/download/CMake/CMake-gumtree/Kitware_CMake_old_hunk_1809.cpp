      fprintf(fout, ")\n");
      }
    
    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",argv[2].c_str());
    fclose(fout);
    projectName = "CMAKE_TRY_COMPILE";
    targetName = "cmTryCompileExec";