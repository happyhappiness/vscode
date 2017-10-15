DownloadList::hash_done(Download* download) {
  check_contains(download);

  if (!download->is_open())
    throw torrent::client_error("DownloadList::hash_done(...) !download->is_open().");

  if (!download->is_hash_checked() || download->is_hash_checking() || download->is_active())
    throw torrent::client_error("DownloadList::hash_done(...) download in invalid state.");

  // Need to find some sane conditional here. Can we check the total
  // downloaded to ensure something was transferred, thus we didn't
  // just hash an already completed torrent with lacking session data?
  //
  // Perhaps we should use a seperate variable or state, and check
  // that. Thus we can bork the download if the hash check doesn't
  // confirm all the data, avoiding large BW usage on f.ex. the
  // ReiserFS bug with >4GB files.

  int64_t hashing = download->variable()->get_value("hashing");
  download->variable()->set("hashing", Download::variable_hashing_stopped);

  switch (hashing) {
  case Download::variable_hashing_initial:
  case Download::variable_hashing_rehash:
    // Normal re/hashing.

    if (download->is_done())
      download->variable()->set("complete", (int64_t)1);
    
    // Save resume data so we update time-stamps and priorities if
    // they were invalid/changed when loading.
    download->download()->hash_resume_save();

    if (download->variable()->get_value("state") == 1)
      resume(download);

    break;

