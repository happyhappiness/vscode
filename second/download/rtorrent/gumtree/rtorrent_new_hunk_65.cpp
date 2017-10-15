		  d.get_chunks_size());
  m_canvas->print(0, y++, "Created: %s",
		  print_ddmmyyyy(static_cast<time_t>(d.get_creation_date())).c_str());

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

