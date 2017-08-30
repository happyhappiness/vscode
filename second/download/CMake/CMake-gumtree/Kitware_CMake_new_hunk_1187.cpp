       }
    } else {
      if (!isFirstLine || !startsWith(line, srcfile)) {
        if (!ignoreErrors) {
          // suppress errors when cl is fed with a rc file
          fprintf(stdout, "%s\n", line.c_str());
        }
      } else {
        isFirstLine = false;
      }
    }
  }

  if (!success) {
    if (ignoreErrors) {
      //printf("\n-- RC file %i dependencies in %s\n\n", includes.size(), dfile.c_str());
      outputDepFile(dfile, objfile, includes);
    }
    return exit_code;
  }

  // don't update .d until/unless we succeed compilation
  outputDepFile(dfile, objfile, includes);

  return 0;
}


int main() {

  // Use the Win32 api instead of argc/argv so we can avoid interpreting the
  // rest of command line after the .d and .obj. Custom parsing seemed
  // preferable to the ugliness you get into in trying to re-escape quotes for
  // subprocesses, so by avoiding argc/argv, the subprocess is called with
  // the same command line verbatim.

  string lang, srcfile, dfile, objfile, prefix, cl, binpath, rest;
  parseCommandLine(GetCommandLine(), lang, srcfile, dfile, objfile,
                                     prefix, cl, binpath, rest);

#if 0
  fprintf(stderr, "\n\ncmcldebug:\n");
  fprintf(stderr, ".d  : %s\n", dfile.c_str());
  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
  fprintf(stderr, "CL  : %s\n", clpath.c_str());
  fprintf(stderr, "REST: %s\n", rest.c_str());
  fprintf(stderr, "\n\n");
#endif

  if (lang != "RC") {
    return process(false, srcfile, dfile, objfile, prefix, binpath + " /showIncludes " + rest);
  } else {
    // "misuse" cl.exe to get headers from .rc files
    // rc: /fo  x\CMakeFiles\x.dir\x.rc.res              src\x\x.rc
    // cl: /out:x\CMakeFiles\x.dir\x.rc.res.dep.obj  /Tc src\x\x.rc

    cl = "\"" + cl + "\" /showIncludes ";
    string clRest = rest;
    clRest = replace(clRest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");

    int ret;
    ret = process(true,  srcfile, dfile, objfile, prefix, cl + clRest);
    ret = process(false, srcfile, ""   , objfile, prefix, binpath + " " + rest);
    return ret;
  }

}