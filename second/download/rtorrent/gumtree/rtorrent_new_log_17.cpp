m_canvas->print(x, y, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    p.get_dns().c_str());