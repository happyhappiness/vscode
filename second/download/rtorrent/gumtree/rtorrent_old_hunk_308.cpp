  // TODO: Make this depend on tracker signal.
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  unsigned int pos = 0;
  torrent::TrackerList* tl = m_download->tracker_list();

  m_canvas->print(2, pos, "Trackers: [Key: %08x]", tl->key());
  ++pos;

  if (tl->size() == 0 || *m_focus >= tl->size())
    return;

  typedef std::pair<unsigned int, unsigned int> Range;
