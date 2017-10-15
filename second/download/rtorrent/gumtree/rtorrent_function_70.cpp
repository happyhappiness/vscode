void
WindowPeerInfo::redraw() {
  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);
  m_canvas->erase();

  int y = 0;
  torrent::Download d = m_download->get_download();

  m_canvas->print(0, y++, "Hash:    %s", utils::string_to_hex(d.get_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", utils::escape_string(d.get_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d.get_chunks_done(),
		  d.get_chunks_total(),
		  d.get_chunks_size());
  m_canvas->print(0, y++, "Created: %s",
		  print_ddmmyyyy(static_cast<time_t>(d.get_creation_date())).c_str());

  y++;

  if (*m_focus == m_list->end()) {
    m_canvas->print(0, y++, "No peer in focus");

    return;
  }

  m_canvas->print(0, y++, "*** Peer Info ***");

  m_canvas->print(0, y++, "DNS: %s:%hu", (*m_focus)->get_dns().c_str(), (*m_focus)->get_port());
  m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->get_id()).c_str());
  m_canvas->print(0, y++, "Options: %s" , utils::string_to_hex(std::string((*m_focus)->get_options(), 8)).c_str());
  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->get_snubbed() ? "yes" : "no");
  m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");

  m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));

  m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->get_write_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_read_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_write_rate().total() / (double)(1 << 20),
		  (double)(*m_focus)->get_read_rate().total() / (double)(1 << 20));
}