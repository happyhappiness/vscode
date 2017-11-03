void
ElementDownloadList::receive_check_hash() {
  if (m_view->focus() == m_view->end_visible())
    return;

  // Catch here?
  control->core()->download_list()->check_hash(*m_view->focus());
}