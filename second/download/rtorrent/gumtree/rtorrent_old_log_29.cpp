m_canvas->print(0, pos++, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    d.get_name().c_str());