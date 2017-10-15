  // ReiserFS bug with >4GB files.

  int64_t hashing = download->variable()->get_value("hashing");
  download->variable()->set("hashing", Download::variable_hashing_stopped);

  switch (hashing) {
  case Download::variable_hashing_started:
    // Normal re/hashing.

    if (download->is_done())
      download->variable()->set("complete", (int64_t)1);
    
    // Save resume data so we update time-stamps and priorities if
    // they were invalid/changed when loading.
    download->download()->hash_resume_save();

    if (download->variable()->get_value("state") == 1)
      resume(download);

    return;

  case Download::variable_hashing_last:

    if (download->is_done()) {

      confirm_finished(download);

      if (download->variable()->get_value("state") == 1)
	resume(download);

    } else {
      download->set_message("Hash check on download completion found bad chunks.");
    }
    
    return;

  case Download::variable_hashing_stopped:
  default:
    // Either an error or someone wrote to the hashing variable...
    download->set_message("Hash check completed but the \"hashing\" variable is in an invalid state.");
    return;
  }
}

void
DownloadList::received_finished(Download* download) {
  check_contains(download);

  if (control->variable()->get_value("check_hash")) {
    // Set some 'checking_finished_thingie' variable to make hash_done
    // trigger correctly, also so it can bork on missing data.

    download->variable()->set("hashing", Download::variable_hashing_last);
    check_hash_throw(download);

  } else {
    confirm_finished(download);
  }
}

// The download must be open when we call this function.
void
DownloadList::confirm_finished(Download* download) {
  check_contains(download);

  // FIXME
  //torrent::download_set_priority(m_download, 2);

  download->variable()->set("complete", (int64_t)1);
  download->set_connection_type(download->variable()->get_string("connection_seed"));

  download->download()->tracker_list().send_completed();

  // Do this before the slots are called in case one of them closes
  // the download.
  if (!download->is_active() && control->variable()->get_value("session_on_completion") == 1) {
    download->download()->hash_resume_save();
    control->core()->download_store()->save(download);
  }

  std::for_each(m_slotMapFinished.begin(), m_slotMapFinished.end(), download_list_call(download));
}

}
