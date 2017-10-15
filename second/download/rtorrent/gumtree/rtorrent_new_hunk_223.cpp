  if (m_view->focus() == m_view->end_visible())
    return;

  const std::string& tiedFile = rpc::call_command_d_string("get_d_tied_to_file", *m_view->focus());

  if (!tiedFile.empty()) {
    rpc::call_command_d_void("d_delete_tied", *m_view->focus());

    control->core()->push_log("Cleared tied to file association for the selected download.");
  }
}

void
ElementDownloadList::receive_change_view(const std::string& name) {
  core::ViewManager::iterator itr = control->view_manager()->find(name);

  if (itr == control->view_manager()->end()) {
    control->core()->push_log_std("Could not find view \"" + name + "\".");
    return;
  }

  set_view(*itr);
}

