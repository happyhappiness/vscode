  utils::displayScheduler.insert(&m_taskUpdate, (utils::Timer::cache() + 1000000).round_seconds());
  m_canvas->erase();

  int y = 0;
  torrent::Download d = m_download->get_download();

  m_canvas->print(0, y++, "Hash:    %s", utils::string_to_hex(d.get_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", utils::escape_string(d.get_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d.get_chunks_done(),
		  d.get_chunks_total(),
		  d.get_chunks_size());

  char buffer[32], *position;
  position = print_ddmmyyyy(buffer, 32, static_cast<time_t>(d.get_creation_date()));
  position = print_string(position, buffer + 32 - position, " ");
  position = print_hhmmss(position, buffer + 32 - position, static_cast<time_t>(d.get_creation_date()));

  m_canvas->print(0, y++, "Created: %s", buffer);

  y++;

  m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
