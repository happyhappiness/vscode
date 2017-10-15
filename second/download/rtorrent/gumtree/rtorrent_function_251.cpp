void
WindowFileList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  torrent::FileList fl = m_download->download()->file_list();

  if (fl.size() == 0 || m_canvas->height() < 2)
    return;

  int pos = 0;

  m_canvas->print( 2, pos, "File");
  m_canvas->print(55, pos, "Size");
  m_canvas->print(63, pos, "Pri");
  m_canvas->print(68, pos, "Cmpl");
  m_canvas->print(74, pos, "Encoding");
  m_canvas->print(84, pos, "Chunks");

  ++pos;

  if (*m_focus >= fl.size())
    throw std::logic_error("WindowFileList::redraw() called on an object with a bad focus value");

  Range range = rak::advance_bidirectional<unsigned int>(0, *m_focus, fl.size(), m_canvas->height() - pos);

  while (range.first != range.second) {
    torrent::File e = fl.get(range.first);

    std::string path = e.path_str();

    if (path.length() <= 50)
      path = path + std::string(50 - path.length(), ' ');
    else
      path = path.substr(0, 50);

    std::string priority;

    switch (e.priority()) {
    case torrent::PRIORITY_OFF:
      priority = "off";
      break;

    case torrent::PRIORITY_NORMAL:
      priority = "   ";
      break;

    case torrent::PRIORITY_HIGH:
      priority = "hig";
      break;

    default:
      priority = "BUG";
      break;
    };

    m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d  %9s",
                    range.first == *m_focus ? '*' : ' ',
                    path.c_str(),
                    (double)e.size_bytes() / (double)(1 << 20),
                    priority.c_str(),
                    done_percentage(e),
                    e.path()->encoding().c_str());

    m_canvas->print(84, pos, "%i - %i %c%c",
                    e.chunk_begin(),
                    e.chunk_begin() != e.chunk_end() ? (e.chunk_end() - 1) : e.chunk_end(),
                    e.is_created() ? 'E' : 'M',
                    e.is_correct_size() ? 'C' : 'W');

    ++range.first;
    ++pos;
  }

}