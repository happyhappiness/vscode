void
DownloadStore::enable(bool lock) {
  if (is_enabled())
    throw torrent::input_error("Session directory already enabled.");

  if (m_path.empty())
    return;

  if (lock)
    m_lockfile.set_path(m_path + "rtorrent.lock");
  else
    m_lockfile.set_path(std::string());

  if (!m_lockfile.try_lock())
    if (rak::error_number::current().is_bad_path())
      throw torrent::input_error("Could not lock session directory: \"" + m_path + "\", " + rak::error_number::current().c_str());
    else
      throw torrent::input_error("Could not lock session directory: \"" + m_path + "\", held by \"" + m_lockfile.locked_by_as_string() + "\".");
}