    return;
  } 

  m_canvas->erase();
  m_canvas->print(0, 0, "Http [%i]", m_queue->size());

  int pos = 10;
  Container::iterator itr = m_container.begin();

  while (itr != m_container.end() && pos + 20 < m_canvas->get_width()) {
    if (itr->m_http == NULL)
      m_canvas->print(pos, 0, "%s done", itr->m_name.c_str());

    else if (itr->m_http->size_total() == 0)
      m_canvas->print(pos, 0, "%s ---%%", itr->m_name.c_str());

    else
      m_canvas->print(pos, 0, "%s %3i%%",
		      itr->m_name.c_str(),
		      (int)(100.0 * itr->m_http->size_done() / itr->m_http->size_total()));

    pos += itr->m_name.size() + 6;
    ++itr;
  }
}

