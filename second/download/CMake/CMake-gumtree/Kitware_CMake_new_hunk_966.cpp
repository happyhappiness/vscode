  if (!out)
    return;

  std::string tmp = objfile;
  doEscape(tmp, " ", "\\ ");
  fprintf(out, "%s: \\\n", tmp.c_str());

  for (std::vector<std::string>::iterator i(incs.begin()); i != incs.end(); ++i) {
    tmp = *i;
    doEscape(tmp, "\\", "/");
    doEscape(tmp, " ", "\\ ");
