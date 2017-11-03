void
DownloadList::disable() {
  if (!is_active())
    throw std::logic_error("ui::DownloadList::disable() called on an already disabled object");

  receive_exit_input(INPUT_NONE);
  activate_display(DISPLAY_MAX_SIZE);

  m_frame = NULL;

  control->input()->erase(&m_bindings);
}