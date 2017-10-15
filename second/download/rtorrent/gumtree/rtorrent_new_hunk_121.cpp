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
		  m_download->variable()->get("connection_leech").as_string().c_str());
  m_canvas->print(0, y++, "Priority:        %u", torrent::download_priority(*m_download->download()));

  m_canvas->print(0, y++, "Directory:       %s", m_download->variable_string("directory").c_str());
  m_canvas->print(0, y++, "Tied to file:    %s", m_download->variable_string("tied_to_file").c_str());

  y++;

  // Temporary.
//   m_canvas->print(0, y++, "SndBuf:          %u", torrent::connection_manager()->send_buffer_size());
//   m_canvas->print(0, y++, "RcvBuf:          %u", torrent::connection_manager()->receive_buffer_size());

//   y++;

  if (*m_focus == m_list->end()) {
    m_canvas->print(0, y++, "No peer in focus");

    return;
  }

  m_canvas->print(0, y++, "*** Peer Info ***");

  m_canvas->print(0, y++, "IP: %s:%hu",
		  rak::socket_address::cast_from((*m_focus)->address())->address_str().c_str(),
		  rak::socket_address::cast_from((*m_focus)->address())->port());

  m_canvas->print(0, y++, "ID: %s" , rak::copy_escape_html((*m_focus)->id()).c_str());

  char buf[128];
  control->client_info()->print(buf, buf + 128, (*m_focus)->id().c_str());

  m_canvas->print(0, y++, "Client: %s" , buf);

  m_canvas->print(0, y++, "Options: %s" , rak::transform_hex(std::string((*m_focus)->options(), 8)).c_str());
  m_canvas->print(0, y++, "Snubbed: %s", (*m_focus)->is_snubbed() ? "yes" : "no");
  m_canvas->print(0, y++, "Connected: %s", (*m_focus)->is_incoming() ? "remote" : "local");

  m_canvas->print(0, y++, "Done: %i%", done_percentage(**m_focus));

