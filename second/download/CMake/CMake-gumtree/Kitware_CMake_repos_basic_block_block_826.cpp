{

  if (dfile.empty())
    return;

  // strip duplicates
  std::sort(incs.begin(), incs.end());
  incs.erase(std::unique(incs.begin(), incs.end()), incs.end());

  FILE* out = cmsys::SystemTools::Fopen(dfile.c_str(), "wb");

  // FIXME should this be fatal or not? delete obj? delete d?
  if (!out)
    return;
  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
  replaceAll(cwd, "/", "\\");
  cwd += "\\";

  std::string tmp = objfile;
  escapePath(tmp);
  fprintf(out, "%s: \\\n", tmp.c_str());

  std::vector<std::string>::iterator it = incs.begin();
  for (; it != incs.end(); ++it) {
    tmp = *it;
    // The paths need to match the ones used to identify build artifacts in the
    // build.ninja file.  Therefore we need to canonicalize the path to use
    // backward slashes and relativize the path to the build directory.
    replaceAll(tmp, "/", "\\");
    if (startsWith(tmp, cwd))
      tmp = tmp.substr(cwd.size());
    escapePath(tmp);
    fprintf(out, "%s \\\n", tmp.c_str());
  }

  fprintf(out, "\n");
  fclose(out);
}