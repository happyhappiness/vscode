m_canvas->print(0, pos++, "%c Group: %2i Id: %s Enabled: %s Open: %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.get_group(),
		    utils::escape_string(t.get_tracker_id()).c_str(),
		    t.is_enabled() ? "yes" : "no",
		    t.is_open() ? "yes" : "no");