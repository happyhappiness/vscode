void
ElementFileList::activate(display::Frame* frame, bool focus) {
  if (m_window != NULL)
    throw torrent::internal_error("ui::ElementFileList::activate(...) is_active().");

  if (focus)
    control->input()->push_back(&m_bindings);

  m_window = new WFileList(this);
  m_window->set_active(true);
  m_window->set_focused(focus);

  m_elementInfo = element_file_list_create_info();
  m_elementInfo->slot_exit(sigc::bind(sigc::mem_fun(this, &ElementFileList::activate_display), DISPLAY_LIST));
  m_elementInfo->set_object(&m_selected);

  m_frame = frame;

  activate_display(DISPLAY_LIST);
}