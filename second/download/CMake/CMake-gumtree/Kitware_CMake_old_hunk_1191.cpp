  string srcfile, dfile, objfile, prefix, clpath, rest;
  parseCommandLine(GetCommandLine(), srcfile, dfile, objfile, prefix, clpath, rest);

  //fprintf(stderr, "D: %s\n", dfile.c_str());
  //fprintf(stderr, "OBJ: %s\n", objfile.c_str());
  //fprintf(stderr, "CL: %s\n", clpath.c_str());
  //fprintf(stderr, "REST: %s\n", rest.c_str());

  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add(clpath + " /showIncludes " + rest);