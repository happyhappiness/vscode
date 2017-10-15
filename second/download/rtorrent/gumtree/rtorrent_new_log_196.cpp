m_canvas->print(0, pos++, "%c Group: %2i Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
		    range.first == *m_focus ? '*' : ' ',
		    t.group(),
		    rak::copy_escape_html(t.tracker_id()).c_str(),
		    range.first == tl->focus() ? "yes" : " no",
		    t.is_enabled() ? "yes" : " no",
		    t.is_open() ? "yes" : " no",
		    t.scrape_complete(),
		    t.scrape_incomplete());