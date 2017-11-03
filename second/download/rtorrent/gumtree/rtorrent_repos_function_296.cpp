void
ElementFileList::receive_prev() {
  torrent::FileList* fl = m_download->download()->file_list();

  if (m_selected == iterator(fl->begin()))
    m_selected = iterator(fl->end());

  if (is_collapsed())
    m_selected.backward_current_depth();
  else
    m_selected--;

  update_itr();
}