WindowTrackerList::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  int pos = 0;
  torrent::TrackerList* tl = m_download->tracker_list();

  m_canvas->print(2, pos, "Trackers: [Key: %08x]", tl->key());
  ++pos;

  if (tl->size() == 0)
    return;

  if (*m_focus >= tl->size())
    throw std::logic_error("WindowTrackerList::redraw() called on an object with a bad focus value.");

  typedef std::pair<unsigned int, unsigned int> Range;

  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, tl->size(), (m_canvas->get_height() + 1) / 2);

  while (range.first != range.second) {
    torrent::Tracker t = tl->get(range.first);

    m_canvas->print(0, pos++, "%c %s",
		    range.first == *m_focus ? '*' : ' ',
		    t.url().c_str());

    m_canvas->print(0, pos++, "%c Group: %2i Id: %s Focus: %s Enabled: %s Open: %s S/L: %u/%u",
		    range.first == *m_focus ? '*' : ' ',
		    t.group(),
		    rak::copy_escape_html(t.tracker_id()).c_str(),
		    range.first == tl->focus() ? "yes" : " no",
		    t.is_enabled() ? "yes" : " no",
		    t.is_open() ? "yes" : " no",
		    t.scrape_complete(),
		    t.scrape_incomplete());

    ++range.first;
  }
}

}
