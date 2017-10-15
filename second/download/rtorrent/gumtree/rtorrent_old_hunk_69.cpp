void
WindowLog::redraw() {
  m_canvas->erase();

  int pos = 0;

  for (core::Log::iterator itr = m_log->begin(), end = find_older(); itr != end && pos < m_canvas->get_height(); ++itr)
    m_canvas->print(0, pos++, "(%s) %s",
		    print_hhmmss(itr->first).c_str(),
		    itr->second.c_str());
}

void
WindowLog::receive_update() {
  iterator itr = find_older();
  int h = std::min(std::distance(m_log->begin(), itr), (std::iterator_traits<iterator>::difference_type)10);
