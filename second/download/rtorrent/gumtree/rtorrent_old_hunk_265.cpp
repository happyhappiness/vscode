ElementDownloadList::receive_prev() {
  m_view->prev_focus();
  m_view->set_last_changed();
}

void
ElementDownloadList::receive_stop_download() {
  if (m_view->focus() == m_view->end_visible())
    return;

  if (rpc::call_command_value("d.get_state", rpc::make_target(*m_view->focus())) == 1)
    control->core()->download_list()->stop_normal(*m_view->focus());
  else
    control->core()->download_list()->erase_ptr(*m_view->focus());

  m_view->set_last_changed();
}

void
ElementDownloadList::receive_close_download() {
  if (m_view->focus() == m_view->end_visible())
    return;

  core::Download* download = *m_view->focus();

  rpc::call_command("d.set_ignore_commands", (int64_t)1, rpc::make_target(download));

  control->core()->download_list()->stop_normal(download);
  control->core()->download_list()->close(download);
  m_view->set_last_changed();
}

void
ElementDownloadList::receive_next_priority() {
  if (m_view->focus() == m_view->end_visible())
    return;

  (*m_view->focus())->set_priority(((*m_view->focus())->priority() + 1) % 4);
  m_window->mark_dirty();
}

void
ElementDownloadList::receive_prev_priority() {
  if (m_view->focus() == m_view->end_visible())
    return;

  (*m_view->focus())->set_priority(((*m_view->focus())->priority() - 1) % 4);
  m_window->mark_dirty();
}

void
ElementDownloadList::receive_ignore_ratio() {
  if (m_view->focus() == m_view->end_visible())
    return;

  if (rpc::call_command_value("d.get_ignore_commands", rpc::make_target(*m_view->focus())) != 0) {
    rpc::call_command_set_value("d.set_ignore_commands", (int64_t)0, rpc::make_target(*m_view->focus()));
    control->core()->push_log("Torrent set to heed commands.");
  } else {
    rpc::call_command_set_value("d.set_ignore_commands", (int64_t)1, rpc::make_target(*m_view->focus()));
    control->core()->push_log("Torrent set to ignore commands.");
  }
}

void
ElementDownloadList::receive_clear_tied() {
  if (m_view->focus() == m_view->end_visible())
    return;

  const std::string& tiedFile = rpc::call_command_string("d.get_tied_to_file", rpc::make_target(*m_view->focus()));

  if (!tiedFile.empty()) {
    rpc::call_command_void("d.delete_tied", rpc::make_target(*m_view->focus()));

    control->core()->push_log("Cleared tied to file association for the selected download.");
  }
}

void
ElementDownloadList::receive_change_view(const std::string& name) {
  core::ViewManager::iterator itr = control->view_manager()->find(name);

  if (itr == control->view_manager()->end()) {
    control->core()->push_log_std("Could not find view \"" + name + "\".");
    return;
