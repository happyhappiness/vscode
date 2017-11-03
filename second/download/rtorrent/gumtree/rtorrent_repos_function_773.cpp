bool
Directory::update(bool hideDot) {
  if (m_path.empty())
    throw std::logic_error("Directory::update() tried to open an empty path");

  DIR* d = opendir(rak::path_expand(m_path).c_str());

  if (d == NULL)
    return false;

  struct dirent* ent;

  while ((ent = readdir(d)) != NULL) {
    std::string de(ent->d_name);

    if (!de.empty() && (!hideDot || de[0] != '.'))
      Base::push_back(ent->d_name);
  }

  closedir(d);
  Base::sort(std::less<std::string>());

  return true;
}