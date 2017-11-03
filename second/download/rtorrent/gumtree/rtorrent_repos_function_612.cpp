void
WindowLog::redraw() {
  m_canvas->erase();

  int pos = m_canvas->height();

  for (core::Log::iterator itr = m_log->begin(), last = find_older(); itr != last && pos > 0; ++itr, --pos) {
    char buffer[16];
    print_hhmmss_local(buffer, buffer + 16, static_cast<time_t>(itr->first.seconds()));

    m_canvas->print(0, pos - 1, "(%s) %s", buffer, itr->second.c_str());
  }
}