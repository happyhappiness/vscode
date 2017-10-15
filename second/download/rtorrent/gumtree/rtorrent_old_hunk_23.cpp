
  int pos = 0;

  //m_canvas->print(std::max(0, (int)m_canvas->get_width() / 2 - 5), pos++, "*** Log ***");
  m_canvas->print(0, 0, "___");

  for (core::Log::iterator itr = m_log->begin(), end = find_older(); itr != end && pos < m_minHeight; ++itr)
    m_canvas->print(0, pos++, "<date>: %s", itr->second.c_str());
}

void
WindowLog::receive_update() {
  iterator itr = find_older();
  int h = std::distance(m_log->begin(), itr);

  if (h != m_minHeight) {
    set_active(h != 0);

    m_minHeight = h;
    m_slotAdjust();
