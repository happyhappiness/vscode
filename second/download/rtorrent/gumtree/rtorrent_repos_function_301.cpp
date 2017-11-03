void
ElementFileList::receive_change_all() {
  if (m_window == NULL)
    return;

  torrent::FileList* fl = m_download->download()->file_list();
  torrent::priority_t priority = torrent::priority_t((m_selected.file()->priority() + 2) % 3);

  for (torrent::FileList::iterator itr = fl->begin(), last = fl->end(); itr != last; ++itr)
    (*itr)->set_priority(priority);

  m_download->download()->update_priorities();
  update_itr();
}