  if (!out)
    return;

  string tmp = objfile;
  doEscape(tmp, " ", "\\ ");
  fprintf(out, "%s: \\\n", tmp.c_str());

  for (vector<string>::iterator i(incs.begin()); i != incs.end(); ++i) {
    tmp = *i;
    doEscape(tmp, "\\", "\\\\");
    doEscape(tmp, " ", "\\ ");
    //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )
