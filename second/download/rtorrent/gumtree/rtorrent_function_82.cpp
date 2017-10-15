void
WindowLogComplete::redraw() {
  m_canvas->erase();

  int pos = 0;

  m_canvas->print(std::max(0, (int)m_canvas->get_width() / 2 - 5), pos++, "*** Log ***");

  for (core::Log::iterator itr = m_log->begin(), e = m_log->end(); itr != e && pos < m_canvas->get_height(); ++itr)
    m_canvas->print(0, pos++, "(%s) %s",
		    print_hhmmss(itr->first).c_str(),
		    itr->second.c_str());
}