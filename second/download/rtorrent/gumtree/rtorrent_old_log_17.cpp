m_canvas->print(x, y, "%c %s",
	     itr == *m_focus ? '*' : ' ',
	     itr->get_dns().c_str());