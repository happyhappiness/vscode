void
ElementFileList::receive_priority() {
  if (m_window == NULL)
    return;

  torrent::priority_t priority = torrent::priority_t((m_selected.file()->priority() + 2) % 3);

  iterator first = m_selected; 
  iterator last = m_selected;
  last.forward_current_depth();

  while (first != last) {
    if (first.is_file())
      first.file()->set_priority(priority);

    first++;
  }

  m_download->download()->update_priorities();
  update_itr();
}