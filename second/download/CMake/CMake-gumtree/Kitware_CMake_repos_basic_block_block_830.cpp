{

  // Use the Win32 API instead of argc/argv so we can avoid interpreting the
  // rest of command line after the .d and .obj. Custom parsing seemed
  // preferable to the ugliness you get into in trying to re-escape quotes for
  // subprocesses, so by avoiding argc/argv, the subprocess is called with
  // the same command line verbatim.

  std::string lang, srcfile, dfile, objfile, prefix, cl, binpath, rest;
  parseCommandLine(GetCommandLineW(), lang, srcfile, dfile, objfile, prefix,
                   cl, binpath, rest);

  // needed to suppress filename output of msvc tools
  std::string srcfilename;
  {
    std::string::size_type pos = srcfile.rfind('\\');
    if (pos == std::string::npos) {
      srcfilename = srcfile;
    } else {
      srcfilename = srcfile.substr(pos + 1);
    }
  }

  std::string nol = " /nologo ";
  std::string show = " /showIncludes ";
  if (lang == "C" || lang == "CXX") {
    return process(srcfilename, dfile, objfile, prefix,
                   binpath + nol + show + rest);
  } else if (lang == "RC") {
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

  usage("Invalid language specified.");
  return 1;
}