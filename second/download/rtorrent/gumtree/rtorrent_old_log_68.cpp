m_canvas->print(0, pos++, "%c Group: %2i Id: %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.get_group(),
		    utils::escape_string(t.get_tracker_id()).c_str());