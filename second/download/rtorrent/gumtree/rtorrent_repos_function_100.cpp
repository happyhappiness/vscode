void
initialize_command_tracker() {
  ADD_CT_STRING_UNI("url",              std::mem_fun(&torrent::Tracker::url));
  ADD_CT_VALUE_UNI("group",             std::mem_fun(&torrent::Tracker::group));
  ADD_CT_VALUE_UNI("type",              std::mem_fun(&torrent::Tracker::tracker_type));
  ADD_CT_STRING_UNI("id",               std::mem_fun(&torrent::Tracker::tracker_id));

  ADD_CT_VALUE_BI("enabled",            std::ptr_fun(&apply_t_set_enabled), std::mem_fun(&torrent::Tracker::is_enabled));

  ADD_CT_VALUE_UNI("is_open",           std::mem_fun(&torrent::Tracker::is_open));

  ADD_CT_VALUE_UNI("normal_interval",   std::mem_fun(&torrent::Tracker::normal_interval));
  ADD_CT_VALUE_UNI("min_interval",      std::mem_fun(&torrent::Tracker::min_interval));

  ADD_CT_VALUE_UNI("scrape_time_last",  std::mem_fun(&torrent::Tracker::scrape_time_last));
  ADD_CT_VALUE_UNI("scrape_complete",   std::mem_fun(&torrent::Tracker::scrape_complete));
  ADD_CT_VALUE_UNI("scrape_incomplete", std::mem_fun(&torrent::Tracker::scrape_incomplete));
  ADD_CT_VALUE_UNI("scrape_downloaded", std::mem_fun(&torrent::Tracker::scrape_downloaded));
}