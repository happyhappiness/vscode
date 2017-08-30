  return str.find(what) != std::string::npos;
}

int main() {

  // Use the Win32 api instead of argc/argv so we can avoid interpreting the
  // rest of command line after the .d and .obj. Custom parsing seemed
  // preferable to the ugliness you get into in trying to re-escape quotes for
  // subprocesses, so by avoiding argc/argv, the subprocess is called with
  // the same command line verbatim.

  string srcfile, dfile, objfile, prefix, clpath, rest;
  parseCommandLine(GetCommandLine(), srcfile, dfile, objfile,
                                     prefix, clpath, rest);

#if 0
  fprintf(stderr, "\n\ncmcldebug:\n");
  fprintf(stderr, ".d  : %s\n", dfile.c_str());
  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
  fprintf(stderr, "CL  : %s\n", clpath.c_str());
  fprintf(stderr, "REST: %s\n", rest.c_str());
  fprintf(stderr, "\n\n");
#endif

  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add(clpath + " /showIncludes " + rest);
  if(!subproc)
    return 2;

