  Window(new Canvas, false, 3),
  m_download(d) {
}

void
WindowDownloadStatusbar::redraw() {
  utils::displayScheduler.insert(&m_taskUpdate, (utils::Timer::cache() + 1000000).round_seconds());

  m_canvas->erase();

  char buffer[m_canvas->get_width() - 2];
  char* position;
  char* last = buffer + m_canvas->get_width() - 2;

  position = print_download_info(buffer, last - buffer, m_download);
  m_canvas->print(0, 0, "%s", buffer);

  m_canvas->print(0, 1, "Peers: %i(%i) Min/Max: %i/%i Uploads: %i U/I: %i/%i",
		  (int)m_download->get_download().peers_connected(),
		  (int)m_download->get_download().peers_not_connected(),
		  (int)m_download->get_download().peers_min(),
		  (int)m_download->get_download().peers_max(),
		  (int)m_download->get_download().uploads_max(),
		  (int)m_download->get_download().peers_currently_unchoked(),
		  (int)m_download->get_download().peers_currently_interested());

  position = print_download_status(buffer, last - buffer, m_download);
  m_canvas->print(0, 2, "[%c:%i] %s",
		  m_download->get_download().is_tracker_busy() ? 'C' : ' ',
		  (int)(m_download->get_download().tracker_timeout() / 1000000),
		  buffer);
