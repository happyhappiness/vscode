  if (!out)

    return;



  fprintf(out, "%s: \\\n", objfile.c_str());

  for (vector<string>::iterator i(incs.begin()); i != incs.end(); ++i) {

    string tmp = *i;

    doEscape(tmp, "\\", "\\\\");

    doEscape(tmp, " ", "\\ ");

    //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )

