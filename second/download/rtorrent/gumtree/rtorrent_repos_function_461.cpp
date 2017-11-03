bool
DownloadList::open(Download* download) {
  try {

    open_throw(download);

    return true;

  } catch (torrent::local_error& e) {
    control->core()->push_log(e.what());
    return false;
  }
}