void
WindowPeerInfo::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  int y = 0;
  torrent::Download* d = m_download->download();

  m_canvas->print(0, y++, "Hash:    %s", rak::transform_hex(d->info_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", rak::copy_escape_html(d->local_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d->chunks_done(),
		  d->chunks_total(),
		  d->chunks_size());

  char buffer[32], *position;
  position = print_ddmmyyyy(buffer, buffer + 32, static_cast<time_t>(d->creation_date()));
  position = print_string(position, buffer + 32, " ");
  position = print_hhmmss(position, buffer + 32, static_cast<time_t>(d->creation_date()));

  m_canvas->print(0, y++, "Created: %s", buffer);

  y++;

  m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
		  m_download->variable()->get("connection_current").as_string().c_str(),
		  m_download->variable()->get("connection_seed").as_string().c_str(),
