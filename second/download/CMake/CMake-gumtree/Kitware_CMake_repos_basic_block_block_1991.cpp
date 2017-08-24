{
  size_t const old_size = path.size();
#if defined(_WIN32) && !defined(__CYGWIN__)
  const char pathSep = ';';
#else
  const char pathSep = ':';
#endif
  if (!env) {
    env = "PATH";
  }
  std::string pathEnv;
  if (!SystemTools::GetEnv(env, pathEnv)) {
    return;
  }

  // A hack to make the below algorithm work.
  if (!pathEnv.empty() && *pathEnv.rbegin() != pathSep) {
    pathEnv += pathSep;
  }
  std::string::size_type start = 0;
  bool done = false;
  while (!done) {
    std::string::size_type endpos = pathEnv.find(pathSep, start);
    if (endpos != std::string::npos) {
      path.push_back(pathEnv.substr(start, endpos - start));
      start = endpos + 1;
    } else {
      done = true;
    }
  }
  for (std::vector<std::string>::iterator i = path.begin() + old_size;
       i != path.end(); ++i) {
    SystemTools::ConvertToUnixSlashes(*i);
  }
}