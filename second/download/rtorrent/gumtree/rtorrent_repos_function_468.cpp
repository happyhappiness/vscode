void
DownloadList::stop_normal(Download* download) {
  check_contains(download);

  rpc::call_command_d("d.set_state", download, (int64_t)0);

  pause(download);
}