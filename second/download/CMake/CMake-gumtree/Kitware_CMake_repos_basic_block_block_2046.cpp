{
  if (!filename) {
    return false;
  }
  return SystemTools::FileExists(std::string(filename), isFile);
}