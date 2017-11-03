void
Root::disable_input() {
  if (m_windowInput->input() == NULL)
    throw torrent::internal_error("Root::disable_input() m_windowInput->input() == NULL.");

  m_windowInput->input()->slot_dirty(sigc::slot0<void>());

  m_windowStatusbar->set_active(true);

  m_windowInput->set_active(false);
  m_windowInput->set_focus(false);
  m_windowInput->set_input(NULL);

  control->input()->set_text_input(NULL);
  control->display()->adjust_layout();
}