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
		  core::Download::connection_type_to_string(m_download->get_connection_current()),
		  core::Download::connection_type_to_string(m_download->get_connection_leech()),
