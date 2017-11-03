bool
DownloadList::stop_try(Download* download) {
  check_contains(download);

  if (rpc::call_command_d_value("d.get_ignore_commands", download) != 0)
    return false;

  rpc::call_command_d("d.set_state", download, (int64_t)0);

  pause(download);
  return true;
}