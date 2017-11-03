void
DownloadList::open_throw(Download* download) {
  check_contains(download);

  if (download->download()->is_open())
    return;
  
  download->download()->open();

  std::for_each(slot_map_open().begin(), slot_map_open().end(), download_list_call(download));
}