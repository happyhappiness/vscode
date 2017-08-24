  return str.find(what) != std::string::npos;
}

std::string replace(const std::string& str, const std::string& what, const std::string& replacement) {
  size_t pos = str.find(what);
  if (pos == std::string::npos)
    return str;
  std::string replaced = str;
  return replaced.replace(pos, what.size(), replacement);
}



static int process(bool ignoreErrors,
                    const string& srcfile,
                    const string& dfile,
                    const string& objfile,
                    const string& prefix,
                    const string& cmd) {

  SubprocessSet subprocs;
  Subprocess* subproc = subprocs.Add(cmd);

  if(!subproc)
    return 2;

