  m_canvas->print(68, pos, "Cmpl");
  m_canvas->print(74, pos, "Encoding");
  m_canvas->print(84, pos, "Chunks");

  ++pos;

  if (*m_focus >= fl.size())
    throw std::logic_error("WindowFileList::redraw() called on an object with a bad focus value");

  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, fl.size(), m_canvas->get_height() - pos);

  while (range.first != range.second) {
    torrent::File e = fl.get(range.first);

    std::string path = e.path_str();

    if (path.length() <= 50)
      path = path + std::string(50 - path.length(), ' ');
    else
      path = path.substr(0, 50);

    std::string priority;

    switch (e.priority()) {
    case torrent::File::OFF:
      priority = "off";
      break;

    case torrent::File::NORMAL:
      priority = "   ";
      break;

    case torrent::File::HIGH:
      priority = "hig";
      break;

    default:
      priority = "BUG";
      break;
