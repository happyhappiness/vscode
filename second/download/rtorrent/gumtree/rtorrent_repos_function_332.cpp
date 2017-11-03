void
ElementDownloadList::receive_close_download() {
  if (m_view->focus() == m_view->end_visible())
    return;

  core::Download* download = *m_view->focus();

  rpc::call_command_d("d.set_ignore_commands", download, (int64_t)1);

  control->core()->download_list()->stop_normal(download);
  control->core()->download_list()->close(download);
  m_view->set_last_changed();
}