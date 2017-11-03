void
WindowDownloadList::set_view(core::View* l) {
  m_view = l;

  m_connChanged.disconnect();

  if (m_view != NULL)
    m_connChanged = m_view->signal_changed().connect(sigc::mem_fun(*this, &Window::mark_dirty));
}