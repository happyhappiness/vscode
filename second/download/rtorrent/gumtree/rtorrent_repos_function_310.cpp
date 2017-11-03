void
Download::receive_min_peers(int t) {
  m_windowDownloadStatus->mark_dirty();

  m_download->download()->set_peers_min(std::max(m_download->download()->peers_min() + t, (uint32_t)5));
}