void
DownloadStore::set_path(const std::string& path) {
  if (is_enabled())
    throw torrent::input_error("Tried to change session directory while it is enabled.");

  if (!path.empty() && *path.rbegin() != '/')
    m_path = rak::path_expand(path + '/');
  else
    m_path = rak::path_expand(path);
}