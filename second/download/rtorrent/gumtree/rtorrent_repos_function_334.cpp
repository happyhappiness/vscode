void
ElementDownloadList::receive_prev_priority() {
  if (m_view->focus() == m_view->end_visible())
    return;

  (*m_view->focus())->set_priority(((*m_view->focus())->priority() - 1) % 4);
  m_window->mark_dirty();
}