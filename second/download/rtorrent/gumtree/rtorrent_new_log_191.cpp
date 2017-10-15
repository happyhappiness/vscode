m_canvas->print(x, y, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    rak::socket_address::cast_from(p.address())->address_str().c_str());