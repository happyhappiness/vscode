void
ElementDownloadList::receive_stop_download() {
  if (m_view->focus() == m_view->end_visible())
    return;

  if (rpc::call_command_d_value("d.get_state", *m_view->focus()) == 1)
    control->core()->download_list()->stop_normal(*m_view->focus());
  else
    control->core()->download_list()->erase_ptr(*m_view->focus());

  m_view->set_last_changed();
}