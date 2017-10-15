m_canvas->print(0, pos++, "%c %s",
		    range.first == m_list->get_focus() ? '*' : ' ',
		    print_download_status(*range.first).c_str());