void
Root::cleanup() {
  if (m_control == NULL)
    throw std::logic_error("Root::cleanup() called twice on the same object");

  if (m_downloadList->is_active())
    m_downloadList->disable();

  m_control->display()->root_frame()->clear();

  delete m_downloadList;

  delete m_windowTitle;
  delete m_windowHttpQueue;
  delete m_windowInput;
  delete m_windowStatusbar;

  m_control->input()->erase(&m_bindings);
  m_control = NULL;
}