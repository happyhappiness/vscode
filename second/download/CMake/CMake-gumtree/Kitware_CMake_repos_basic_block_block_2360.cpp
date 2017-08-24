{
  if (!file) {
    return false;
  }
  return SystemTools::GetPermissions(std::string(file), mode);
}