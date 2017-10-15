m_canvas->print(0, pos++, "%c %s",
		    itr == *m_focus ? '*' : ' ',
		    (*itr)->get_download().get_name().c_str());