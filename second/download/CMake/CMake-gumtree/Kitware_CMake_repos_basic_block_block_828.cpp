{
    // "misuse" cl.exe to get headers from .rc files

    std::string clrest = rest;
    // rc: /fo x.dir\x.rc.res  ->  cl: /out:x.dir\x.rc.res.dep.obj
    clrest = replace(clrest, "/fo", "/out:");
    clrest = replace(clrest, objfile, objfile + ".dep.obj ");

    cl = "\"" + cl + "\" /P /DRC_INVOKED /TC ";

    // call cl in object dir so the .i is generated there
    std::string objdir;
    {
      std::string::size_type pos = objfile.rfind("\\");
      if (pos != std::string::npos) {
        objdir = objfile.substr(0, pos);
      }
    }

    // extract dependencies with cl.exe
    int exit_code = process(srcfilename, dfile, objfile, prefix,
                            cl + nol + show + clrest, objdir, true);

    if (exit_code != 0)
      return exit_code;

    // compile rc file with rc.exe
    return process(srcfilename, "", objfile, prefix, binpath + " " + rest);
  }