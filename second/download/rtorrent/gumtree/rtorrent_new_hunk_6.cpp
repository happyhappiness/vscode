  m_list(l),
  m_focus(f) {
}

void
WindowPeerInfo::redraw() {
  if (utils::Timer::cache() - m_lastDraw < 1000000)
    return;

  m_lastDraw = utils::Timer::cache();
  m_canvas->erase();

  int y = 0;

  m_canvas->print(0, y++, "Hash: %s", utils::string_to_hex(m_download->get_download().get_hash()).c_str());
  m_canvas->print(0, y++, "Chunks: %u / %u * %u",
		  m_download->get_download().get_chunks_done(),
		  m_download->get_download().get_chunks_total(),
		  m_download->get_download().get_chunks_size());

  y++;
