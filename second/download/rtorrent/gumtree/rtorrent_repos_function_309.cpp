void
Download::receive_max_uploads(int t) {
  m_windowDownloadStatus->mark_dirty();

  m_download->download()->set_uploads_max(std::max(m_download->download()->uploads_max() + t, (uint32_t)2));
}