  //
  // Perhaps we should use a seperate variable or state, and check
  // that. Thus we can bork the download if the hash check doesn't
  // confirm all the data, avoiding large BW usage on f.ex. the
  // ReiserFS bug with >4GB files.

  int64_t hashing = download->variable()->get_value("hashing");
  download->variable()->set_value("hashing", Download::variable_hashing_stopped);

  switch (hashing) {
  case Download::variable_hashing_initial:
  case Download::variable_hashing_rehash:
    // Normal re/hashing.

    // If the download was previously completed but the files were
    // f.ex deleted, then we clear the state and complete.
    if (download->variable()->get_value("complete") && !download->is_done()) {
      download->variable()->set("state", (int64_t)0);
      download->set_message("Download registered as completed, but hash check returned unfinished chunks.");
    }

    // Save resume data so we update time-stamps and priorities if
    // they were invalid/changed while loading/hashing.
    download->variable()->set("complete", (int64_t)download->is_done());
    torrent::resume_save_progress(*download->download(), download->download()->bencode()->get_key("libtorrent_resume"));

    if (download->variable()->get_value("state") == 1)
      resume(download);

    break;

  case Download::variable_hashing_last:

