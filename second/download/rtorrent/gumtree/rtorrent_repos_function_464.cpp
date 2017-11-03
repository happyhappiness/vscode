void
DownloadList::close_quick(Download* download) {
  close(download);
  
  // Make sure we cancel any tracker requests. This should rather be
  // handled by some parameter to the close function, or some other
  // way of giving the client more control of when STOPPED requests
  // are sent.
  download->download()->tracker_list().manual_cancel();
}