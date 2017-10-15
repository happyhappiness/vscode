m_canvas->print(0, pos++, "%c Tracker: %s",
		    itr == *m_focus ? '*' : ' ',
		    itr->get_download().is_tracker_busy() ? "Connecting" : itr->get_tracker_msg().c_str());