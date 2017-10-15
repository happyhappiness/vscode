  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "yes" : "no");
  m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");

  m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));

  m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->get_up_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_down_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_up_rate().total() / (double)(1 << 20),
		  (double)(*m_focus)->get_down_rate().total() / (double)(1 << 20));
}

int
WindowPeerInfo::done_percentage(torrent::Peer& p) {
  int chunks = m_download->get_download().get_chunks_total();

