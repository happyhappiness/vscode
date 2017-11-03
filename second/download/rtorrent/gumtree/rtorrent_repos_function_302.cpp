void
ElementFileList::receive_collapse() {
  if (m_window == NULL)
    return;

  set_collapsed(!is_collapsed());
  m_window->mark_dirty();
}