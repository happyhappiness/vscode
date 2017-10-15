m_canvas->print(x, y, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    p.address().c_str());