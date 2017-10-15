void
WindowPeerInfo::redraw() {
  priority_queue_insert(&displayScheduler, &m_taskUpdate, (cachedTime + 1000000).round_seconds());
  m_canvas->erase();

  int y = 0;
  torrent::Download d = m_download->get_download();

  m_canvas->print(0, y++, "Hash:    %s", utils::string_to_hex(d.info_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", utils::escape_string(d.local_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d.chunks_done(),
		  d.chunks_total(),
		  d.chunks_size());

  char buffer[32], *position;
  position = print_ddmmyyyy(buffer, 32, static_cast<time_t>(d.creation_date()));
  position = print_string(position, buffer + 32 - position, " ");
  position = print_hhmmss(position, buffer + 32 - position, static_cast<time_t>(d.creation_date()));

  m_canvas->print(0, y++, "Created: %s", buffer);

  y++;

  m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
		  core::Download::connection_type_to_string(m_download->get_connection_current()),
		  core::Download::connection_type_to_string(m_download->get_connection_leech()),
		  core::Download::connection_type_to_string(m_download->get_connection_seed()));

  y++;

  if (*m_focus == m_list->end()) {
    m_canvas->print(0, y++, "No peer in focus");

    return;
  }

  m_canvas->print(0, y++, "*** Peer Info ***");

  m_canvas->print(0, y++, "DNS: %s:%hu", (*m_focus)->address().c_str(), (*m_focus)->port());
  m_canvas->print(0, y++, "Id: %s" , utils::escape_string((*m_focus)->id()).c_str());
  m_canvas->print(0, y++, "Options: %s" , utils::string_to_hex(std::string((*m_focus)->options(), 8)).c_str());
  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->is_snubbed() ? "yes" : "no");
  m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");

  m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));

  m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->up_rate()->rate() / (double)(1 << 10),
		  (double)(*m_focus)->down_rate()->rate() / (double)(1 << 10),
		  (double)(*m_focus)->up_rate()->total() / (double)(1 << 20),
		  (double)(*m_focus)->down_rate()->total() / (double)(1 << 20));
}