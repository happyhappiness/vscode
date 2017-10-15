m_canvas->print(0, y++, "Connection Type: %s ( %s / %s )",
		  m_download->variables()->get("connection_current").as_string().c_str(),
		  m_download->variables()->get("connection_seed").as_string().c_str(),
		  m_download->variables()->get("connection_leech").as_string().c_str());