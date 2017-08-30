  // FIXME should this be fatal or not? delete obj? delete d?

  if (!out)

    return;



  std::string tmp = objfile;

  doEscape(tmp, " ", "\\ ");

  fprintf(out, "%s: \\\n", tmp.c_str());



  std::vector<std::string>::iterator it = incs.begin();

  for (; it != incs.end(); ++it) {

    tmp = *it;

    doEscape(tmp, "\\", "/");

    doEscape(tmp, " ", "\\ ");

    fprintf(out, "%s \\\n", tmp.c_str());

  }



