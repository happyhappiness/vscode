bool
DownloadList::start_try(Download* download) {
  check_contains(download);

  // Also don't start if the state is one of those that indicate we
  // were manually stopped?

  if (download->is_hash_failed() || rpc::call_command_d_value("d.get_ignore_commands", download) != 0)
    return false;

  // Don't clear the hash failed as this function is used by scripts,
  // etc.
  rpc::call_command_d("d.set_state", download, (int64_t)1);

  resume(download);
  return true;
}