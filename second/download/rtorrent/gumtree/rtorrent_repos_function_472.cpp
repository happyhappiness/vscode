void
DownloadList::check_hash(Download* download) {
  check_contains(download);

  try {

    if (rpc::call_command_d_value("d.get_hashing", download) != Download::variable_hashing_stopped)
      return;

    hash_queue(download, Download::variable_hashing_rehash);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}