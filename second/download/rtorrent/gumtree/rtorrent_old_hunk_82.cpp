  int pos = 0;

  m_canvas->print( 2, pos, "Trackers:");

  ++pos;

  if (m_download->get_download().get_tracker_size() == 0)
    return;

  if (*m_focus >= m_download->get_download().get_tracker_size())
    throw std::logic_error("WindowTrackerList::redraw() called on an object with a bad focus value");

  typedef std::pair<unsigned int, unsigned int> Range;

  Range range = rak::advance_bidirectional<unsigned int>(0,
							 *m_focus,
							 m_download->get_download().get_tracker_size(),
							 (m_canvas->get_height() + 1) / 2);

  while (range.first != range.second) {
    torrent::Tracker t = m_download->get_download().get_tracker(range.first);

    m_canvas->print(0, pos++, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.get_url().c_str());

    m_canvas->print(0, pos++, "%c Group: %2i Id: %s Focus: %s Enabled: %s Open: %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.get_group(),
		    utils::escape_string(t.get_tracker_id()).c_str(),
		    range.first == m_download->get_download().get_tracker_focus() ? "yes" : " no",
		    t.is_enabled() ? "yes" : " no",
		    t.is_open() ? "yes" : " no");

    ++range.first;
  }
}
