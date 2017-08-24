{
  if (!file) {
    return false;
  }
  return SystemTools::SetPermissions(std::string(file), mode, honor_umask);
}