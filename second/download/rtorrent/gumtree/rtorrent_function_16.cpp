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

  if (*m_focus == m_list->end()) {
    m_canvas->print(0, y++, "No peer in focus");

    return;
  }

  m_canvas->print(0, y++, "DNS: %s:%hu", (*m_focus)->get_dns().c_str(), (*m_focus)->get_port());
  m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->get_id()).c_str());
  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "Yes" : "No");
  m_canvas->print(0, y++, "Done: %i%", (*m_focus)->get_chunks_done());

  m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->get_rate_up() / (double)(1 << 10),
		  (double)(*m_focus)->get_rate_down() / (double)(1 << 10),
		  (double)(*m_focus)->get_transfered_up() / (double)(1 << 20),
		  (double)(*m_focus)->get_transfered_down() / (double)(1 << 20));
}