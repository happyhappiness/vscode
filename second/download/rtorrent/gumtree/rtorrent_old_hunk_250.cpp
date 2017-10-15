    m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(m_interval)).round_seconds());

  m_canvas->erase();

  unsigned int position = 0;

  for (iterator itr = begin(); itr != end() && position < m_canvas->height(); ++itr, ++position) {
    if (*itr == NULL)
      continue;

    char buffer[m_canvas->width() + 1];

