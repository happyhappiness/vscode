torrent::Tracker*
xmlrpc_find_tracker(core::Download* download, uint32_t index) {
  if (index >= download->tracker_list()->size())
    return NULL;

  // HACK ALERT!!!!
  static torrent::Tracker hack;
  hack = download->tracker_list()->get(index);

  return &hack;
}