void
WindowPeerInfo::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  int y = 0;
  char buffer[256];
  char* position;

  torrent::Download* d = m_download->download();

  m_canvas->print(0, y++, "Hash:    %s", rak::transform_hex(d->info_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", rak::copy_escape_html(d->local_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d->chunks_done(),
		  d->chunks_total(),
		  d->chunks_size());

  y++;

  position = print_date(buffer, buffer + 256, static_cast<time_t>(d->creation_date()));
  m_canvas->print(0, y++, "Created:       %s", buffer);

  position = print_timer(buffer, buffer + 256, static_cast<time_t>(m_download->variable()->get_value("state_changed")));
  m_canvas->print(0, y++, "State Changed: %s", buffer);

  y++;

  m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
		  m_download->variable()->get("connection_current").as_string().c_str(),
		  m_download->variable()->get("connection_seed").as_string().c_str(),
