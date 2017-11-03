void
ElementDownloadList::set_view(core::View* l) {
  m_view = l;
  m_view->sort();

  if (m_window == NULL)
    return;

  m_window->set_view(l);
  m_window->mark_dirty();
}