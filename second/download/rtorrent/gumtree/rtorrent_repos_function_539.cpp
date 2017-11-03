void
DownloadStore::disable() {
  if (!is_enabled())
    return;

  m_lockfile.unlock();
}