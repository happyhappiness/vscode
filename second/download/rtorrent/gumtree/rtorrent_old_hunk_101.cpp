  int pos = 0;

  m_canvas->print(std::max(0, (int)m_canvas->get_width() / 2 - 5), pos++, "*** Log ***");

  for (core::Log::iterator itr = m_log->begin(), e = m_log->end(); itr != e && pos < m_canvas->get_height(); ++itr) {
    char buffer[16];
    print_hhmmss(buffer, 16, static_cast<time_t>(itr->first.seconds()));

    m_canvas->print(0, pos++, "(%s) %s", buffer, itr->second.c_str());
  }
}

void
