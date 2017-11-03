void
ElementFileList::receive_pagenext() {
  torrent::FileList* fl = m_download->download()->file_list();

  if (m_selected == --iterator(fl->end())) {
    m_selected = iterator(fl->begin());

  } else {
    m_selected = rak::advance_forward(m_selected, iterator(fl->end()), (m_window->height() - 1) / 2);

    if (m_selected == iterator(fl->end()))
      m_selected = --iterator(fl->end());
  }

  update_itr();
}