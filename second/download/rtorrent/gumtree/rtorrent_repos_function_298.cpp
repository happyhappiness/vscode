void
ElementFileList::receive_pageprev() {
  if (m_window == NULL)
    return;

  torrent::FileList* fl = m_download->download()->file_list();

  if (m_selected == iterator(fl->begin()))
    m_selected = --iterator(fl->end());
  else
    m_selected = rak::advance_backward(m_selected, iterator(fl->begin()), (m_window->height() - 1) / 2);

  update_itr();
}