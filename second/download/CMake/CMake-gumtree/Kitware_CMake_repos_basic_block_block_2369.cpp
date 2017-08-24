{
  if (cDir.empty()) {
    return false;
  }
  std::string subdir = cSubdir;
  std::string dir = cDir;
  SystemTools::ConvertToUnixSlashes(subdir);
  SystemTools::ConvertToUnixSlashes(dir);
  if (subdir.size() > dir.size() && subdir[dir.size()] == '/') {
    std::string s = subdir.substr(0, dir.size());
    return SystemTools::ComparePath(s, dir);
  }
  return false;
}