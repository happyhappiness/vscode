m_canvas->print(0, pos++, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.url().c_str());