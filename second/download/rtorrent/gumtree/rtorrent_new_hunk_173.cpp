
  if (*m_focus >= tl->size())
    throw std::logic_error("WindowTrackerList::redraw() called on an object with a bad focus value.");

  typedef std::pair<unsigned int, unsigned int> Range;

  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, tl->size(), (m_canvas->height() + 1) / 2);

  while (range.first != range.second) {
    torrent::Tracker t = tl->get(range.first);

    m_canvas->print(0, pos++, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
