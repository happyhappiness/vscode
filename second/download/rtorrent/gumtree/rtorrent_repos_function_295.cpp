void
ElementFileList::receive_next() {
  torrent::FileList* fl = m_download->download()->file_list();

  if (is_collapsed())
    m_selected.forward_current_depth();
  else
    m_selected++;

  if (m_selected == iterator(fl->end()))
    m_selected = iterator(fl->begin());

  update_itr();
}