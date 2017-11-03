bool
Directory::is_valid() const {
  if (m_path.empty())
    return false;

  DIR* d = opendir(rak::path_expand(m_path).c_str());
  closedir(d);

  return d;
}