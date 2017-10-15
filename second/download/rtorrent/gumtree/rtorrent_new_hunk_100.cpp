  m_canvas->erase();

  int pos = 0;

  for (core::Log::iterator itr = m_log->begin(), end = find_older(); itr != end && pos < m_canvas->get_height(); ++itr) {
    char buffer[16];
    print_hhmmss(buffer, buffer + 16, static_cast<time_t>(itr->first.seconds()));

    m_canvas->print(0, pos++, "(%s) %s", buffer, itr->second.c_str());
  }
}

void
