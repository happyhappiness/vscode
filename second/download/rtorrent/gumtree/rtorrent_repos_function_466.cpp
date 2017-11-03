void
DownloadList::start_normal(Download* download) {
  check_contains(download);

  // Clear hash failed as we're doing a manual start and want to try
  // hashing again.
  download->set_hash_failed(false);
  rpc::call_command_d("d.set_state", download, (int64_t)1);

  resume(download);
}