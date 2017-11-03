void
Root::enable_input(const std::string& title, input::TextInput* input) {
  if (m_windowInput->input() != NULL)
    throw torrent::internal_error("Root::enable_input(...) m_windowInput->input() != NULL.");

  input->slot_dirty(sigc::mem_fun(m_windowInput, &WInput::mark_dirty));

  m_windowStatusbar->set_active(false);

  m_windowInput->set_active(true);
  m_windowInput->set_input(input);
  m_windowInput->set_title(title);
  m_windowInput->set_focus(true);

  input->bindings()['\x0C'] = sigc::mem_fun(m_control->display(), &display::Manager::force_redraw); // ^L
  input->bindings()['\x11'] = sigc::mem_fun(m_control, &Control::receive_normal_shutdown); // ^Q

  control->input()->set_text_input(input);
  control->display()->adjust_layout();
}