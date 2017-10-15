m_canvas->print(pos, 0, "%s %3i%%",
		      itr->m_name.c_str(),
		      (int)(100.0 * itr->m_http->get_size_done() / itr->m_http->get_size_total()));