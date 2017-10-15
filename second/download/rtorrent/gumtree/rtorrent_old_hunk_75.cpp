
void
WindowFileList::redraw() {
  utils::displayScheduler.insert(&m_taskUpdate, (utils::Timer::cache() + 10 * 1000000).round_seconds());
  m_canvas->erase();

  if (m_download->get_download().get_entry_size() == 0 ||
      m_canvas->get_height() < 2)
    return;

  int pos = 0;

  m_canvas->print( 2, pos, "File");
  m_canvas->print(55, pos, "Size");
  m_canvas->print(63, pos, "Pri");
  m_canvas->print(68, pos, "Cmpl");

  ++pos;

  if (*m_focus >= m_download->get_download().get_entry_size())
    throw std::logic_error("WindowFileList::redraw() called on an object with a bad focus value");

  Range range = rak::advance_bidirectional<unsigned int>(0,
							 *m_focus,
							 m_download->get_download().get_entry_size(),
							 m_canvas->get_height() - pos);

  while (range.first != range.second) {
    torrent::Entry e = m_download->get_download().get_entry(range.first);

    std::string path = e.get_path();

    if (path.length() <= 50)
      path = path + std::string(50 - path.length(), ' ');
    else
      path = path.substr(0, 50);

    std::string priority;

    switch (e.get_priority()) {
    case torrent::Entry::STOPPED:
      priority = "off";
      break;

    case torrent::Entry::NORMAL:
      priority = "   ";
      break;
