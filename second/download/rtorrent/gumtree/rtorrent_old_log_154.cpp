m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
		  core::Download::connection_type_to_string(m_download->get_connection_current()),
		  core::Download::connection_type_to_string(m_download->get_connection_leech()),
		  core::Download::connection_type_to_string(m_download->get_connection_seed()));