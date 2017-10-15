  m_canvas->print(68, pos, "Cmpl");
  m_canvas->print(74, pos, "Encoding");
  m_canvas->print(84, pos, "Chunks");

  ++pos;

  if (*m_focus >= m_download->get_download().size_file_entries())
    throw std::logic_error("WindowFileList::redraw() called on an object with a bad focus value");

  Range range = rak::advance_bidirectional<unsigned int>(0,
							 *m_focus,
							 m_download->get_download().size_file_entries(),
							 m_canvas->get_height() - pos);

  while (range.first != range.second) {
    torrent::Entry e = m_download->get_download().file_entry(range.first);

    std::string path = e.path_str();

    if (path.length() <= 50)
      path = path + std::string(50 - path.length(), ' ');
    else
      path = path.substr(0, 50);

    std::string priority;

    switch (e.priority()) {
    case torrent::Entry::OFF:
      priority = "off";
      break;

    case torrent::Entry::NORMAL:
      priority = "   ";
      break;

    case torrent::Entry::HIGH:
      priority = "hig";
      break;

    default:
      priority = "BUG";
      break;
