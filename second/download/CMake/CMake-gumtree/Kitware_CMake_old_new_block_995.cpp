{

  // strip duplicates
  sort(incs.begin(), incs.end());
  incs.erase(unique(incs.begin(), incs.end()), incs.end());

  FILE* out = fopen(dfile.c_str(), "wb");

  // FIXME should this be fatal or not? delete obj? delete d?
  if (!out)
    return;

  fprintf(out, "%s: \\\n", objfile.c_str());
  for (vector<string>::iterator i(incs.begin()); i != incs.end(); ++i) {
    string tmp = *i;
    doEscape(tmp, "\\", "\\\\");
    doEscape(tmp, " ", "\\ ");
    //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )
    //doEscape(tmp, ")", ")");
    fprintf(out, "%s \\\n", tmp.c_str());
  }

  fprintf(out, "\n");
  fclose(out);
}