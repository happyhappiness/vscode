m_canvas->print(0, y++, "IP: %s:%hu",
		  rak::socket_address::cast_from((*m_focus)->address())->address_str().c_str(),
		  rak::socket_address::cast_from((*m_focus)->address())->port());