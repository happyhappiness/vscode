void
ElementDownloadList::receive_start_download() {
  if (m_view->focus() == m_view->end_visible())
    return;

  control->core()->download_list()->start_normal(*m_view->focus());
  m_view->set_last_changed();
}