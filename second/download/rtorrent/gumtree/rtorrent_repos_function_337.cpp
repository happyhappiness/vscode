void
ElementDownloadList::receive_clear_tied() {
  if (m_view->focus() == m_view->end_visible())
    return;

  const std::string& tiedFile = rpc::call_command_d_string("d.get_tied_to_file", *m_view->focus());

  if (!tiedFile.empty()) {
    rpc::call_command_d_void("d.delete_tied", *m_view->focus());

    control->core()->push_log("Cleared tied to file association for the selected download.");
  }
}