void
Download::receive_max_peers(int t) {
  m_windowDownloadStatus->mark_dirty();

  m_download->download()->set_peers_max(std::max(m_download->download()->peers_max() + t, (uint32_t)5));
}