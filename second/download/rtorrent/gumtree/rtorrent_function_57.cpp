void
WindowDownloadList::redraw() {
  utils::displayScheduler.insert(&m_taskUpdate, utils::Timer::cache().round_seconds() + 1000000);

  m_canvas->erase();

  if (m_list->base().empty() || m_canvas->get_width() < 5)
    return;

  typedef std::pair<DList::iterator, DList::iterator> Range;

  Range range = rak::advance_bidirectional(m_list->begin(),
					   m_list->get_focus() != m_list->end() ? m_list->get_focus() : m_list->begin(),
					   m_list->end(),
					   m_canvas->get_height() / 3);

  // Make sure we properly fill out the last lines so it looks like
  // there are more torrents, yet don't hide it if we got the last one
  // in focus.
  if (range.second != m_list->end())
    ++range.second;

  int pos = 0;

  while (range.first != range.second) {
    char buffer[m_canvas->get_width() - 2];
    char* position;
    char* last = buffer + m_canvas->get_width() - 2;

    position = print_download_title(buffer, last - buffer, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);
    
    position = print_download_info(buffer, last - buffer, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);

    position = print_download_status(buffer, last - buffer, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_list->get_focus() ? '*' : ' ', buffer);

    ++range.first;
  }    
}