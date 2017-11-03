void
DownloadFactory::initialize_rtorrent(Download* download, torrent::Object* rtorrent) {
  if (!rtorrent->has_key_value("state") || rtorrent->get_key_value("state") > 1) {
    rtorrent->insert_key("state", (int64_t)m_start);
    rtorrent->insert_key("state_changed", cachedTime.seconds());

  } else if (!rtorrent->has_key_value("state_changed") ||
             rtorrent->get_key_value("state_changed") > cachedTime.seconds() || rtorrent->get_key_value("state_changed") == 0) {
    rtorrent->insert_key("state_changed", cachedTime.seconds());
  }

  if (!rtorrent->has_key_value("complete"))
    rtorrent->insert_key("complete", (int64_t)0);

  if (!rtorrent->has_key_value("hashing"))
    rtorrent->insert_key("hashing", (int64_t)Download::variable_hashing_stopped);

  if (!rtorrent->has_key_string("tied_to_file"))
    rtorrent->insert_key("tied_to_file", std::string());

  if (rtorrent->has_key_value("priority"))
    rpc::call_command_d("d.set_priority", download, rtorrent->get_key_value("priority") % 4);
  else
    rpc::call_command_d("d.set_priority", download, (int64_t)2);

  if (rtorrent->has_key_value("key")) {
    download->tracker_list()->set_key(rtorrent->get_key_value("key"));

  } else {
    download->tracker_list()->set_key(random() % (std::numeric_limits<uint32_t>::max() - 1) + 1);
    rtorrent->insert_key("key", download->tracker_list()->key());
  }

  if (rtorrent->has_key_value("total_uploaded"))
    download->download()->up_rate()->set_total(rtorrent->get_key_value("total_uploaded"));

  if (rtorrent->has_key_value("chunks_done"))
    download->download()->set_chunks_done(std::min<uint32_t>(rtorrent->get_key_value("chunks_done"),
                                                             download->download()->file_list()->size_chunks()));

  if (!rtorrent->has_key_value("ignore_commands"))
    rtorrent->insert_key("ignore_commands", (int64_t)0);
}