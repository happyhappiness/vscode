void
DownloadList::close(Download* download) {
  try {

    close_throw(download);

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
  }
}