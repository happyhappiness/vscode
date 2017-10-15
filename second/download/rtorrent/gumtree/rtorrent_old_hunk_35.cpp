
void
WindowFileList::redraw() {
  m_nextDraw = utils::Timer::cache().round_seconds() + 10 * 1000000;
  m_canvas->erase();

  int pos = 0;

  m_canvas->print( 2, pos, "File");
  m_canvas->print(55, pos, "Size");
  m_canvas->print(63, pos, "Pri");
  m_canvas->print(68, pos, "Cmpl");

  ++pos;

  if (m_download->get_download().get_entry_size() == 0)
    return;

  if (*m_focus >= m_download->get_download().get_entry_size())
    throw std::logic_error("WindowFileList::redraw() called on an object with a bad focus value");

  typedef std::pair<unsigned int, unsigned int> Range;

  Range range = rak::advance_bidirectional<unsigned int>(0,
							 *m_focus,
							 m_download->get_download().get_entry_size(),
							 m_canvas->get_height());

  while (range.first != range.second) {
    torrent::Entry e = m_download->get_download().get_entry(range.first);

    std::string path = e.get_path();

