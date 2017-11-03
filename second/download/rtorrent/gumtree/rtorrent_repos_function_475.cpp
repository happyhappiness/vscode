void
DownloadList::received_finished(Download* download) {
  check_contains(download);

  if (rpc::call_command_value("get_check_hash")) {
    // Set some 'checking_finished_thingie' variable to make hash_done
    // trigger correctly, also so it can bork on missing data.
    hash_queue(download, Download::variable_hashing_last);

  } else {
    confirm_finished(download);
  }
}