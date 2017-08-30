  parseCommandLine(GetCommandLine(), lang, srcfile, dfile, objfile,
                                     prefix, cl, binpath, rest);

  // needed to suppress filename output of msvc tools
  string srcfilename;
  std::string::size_type pos = srcfile.rfind("\\");
  if (pos != string::npos) {
    srcfilename = srcfile.substr(pos + 1);
  }

  std::string nol = " /nologo ";
  std::string show = " /showIncludes ";
  if (lang == "C" || lang == "CXX") {
    return process(srcfilename, dfile, objfile, prefix,
                   binpath + nol + show + rest);
  } else if (lang == "RC") {
    // "misuse" cl.exe to get headers from .rc files

    string clrest = rest;
    // rc: /fo x.dir\x.rc.res  ->  cl: /out:x.dir\x.rc.res.dep.obj
    clrest = replace(clrest, "/fo", "/out:");
    clrest = replace(clrest, objfile, objfile + ".dep.obj ");
    // rc: src\x\x.rc  ->  cl: /Tc src\x\x.rc
    clrest = replace(clrest, srcfile, "/Tc " + srcfile);

    cl = "\"" + cl + "\" /P /DRC_INVOKED ";

    // extract dependencies with cl.exe
    process(srcfilename, dfile, objfile,
                  prefix, cl + nol + show + clrest, true);

    // compile rc file with rc.exe
    return process(srcfilename, "" , objfile, prefix, binpath + nol + rest);
  }

  usage("Invalid language specified.");
  return 1;
}