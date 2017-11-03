void
ElementDownloadList::receive_ignore_ratio() {
  if (m_view->focus() == m_view->end_visible())
    return;

  if (rpc::call_command_d_value("d.get_ignore_commands", *m_view->focus()) != 0) {
    rpc::call_command_d_set_value("d.set_ignore_commands", *m_view->focus(), (int64_t)0);
    control->core()->push_log("Torrent set to heed commands.");
  } else {
    rpc::call_command_d_set_value("d.set_ignore_commands", *m_view->focus(), (int64_t)1);
    control->core()->push_log("Torrent set to ignore commands.");
  }
}