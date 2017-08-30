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



  std::string showflag = " /showIncludes /nologo ";

  if (lang != "RC") {

    return process(srcfile, dfile, objfile, prefix,

                   binpath + showflag + rest);

  } else {

    // "misuse" cl.exe to get headers from .rc files

    // rc: /fo  x\CMakeFiles\x.dir\x.rc.res              src\x\x.rc

    // cl: /out:x\CMakeFiles\x.dir\x.rc.res.dep.obj  /Tc src\x\x.rc



    cl = "\"" + cl + "\" /P /DRC_INVOKED " + showflag +

         replace(rest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");



    int ret;

    ret = process(srcfile, dfile, objfile, prefix, cl, true);

    ret = process(srcfile, ""   , objfile, prefix,

                  binpath + " /nologo "  + rest);

    return ret;

  }



}
