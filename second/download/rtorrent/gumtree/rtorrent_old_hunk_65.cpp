		  d.get_chunks_size());
  m_canvas->print(0, y++, "Created: %s",
		  print_ddmmyyyy(static_cast<time_t>(d.get_creation_date())).c_str());

  y++;

  if (*m_focus == m_list->end()) {
    m_canvas->print(0, y++, "No peer in focus");

    return;
  }

