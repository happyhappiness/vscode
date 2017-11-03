void
initialize_command_download() {
  ADD_CD_VOID("base_path",     &retrieve_d_base_path);
  ADD_CD_VOID("base_filename", &retrieve_d_base_filename);
  ADD_CD_STRING_UNI("name",    rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::name)));

  ADD_CD_LIST("create_link",   rak::bind_ptr_fn(&apply_d_change_link, 0));
  ADD_CD_LIST("delete_link",   rak::bind_ptr_fn(&apply_d_change_link, 1));
  ADD_CD_V_VOID("delete_tied", &apply_d_delete_tied);

  ADD_CD_F_VOID("start",      rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::start_normal));
  ADD_CD_F_VOID("stop",       rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::stop_normal));
  ADD_CD_F_VOID("open",       rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::open_throw));
  ADD_CD_F_VOID("close",      rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::close_throw));
  ADD_CD_F_VOID("erase",      rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::erase_ptr));
  ADD_CD_F_VOID("check_hash", rak::make_mem_fun(control->core()->download_list(), &core::DownloadList::check_hash));

  ADD_CD_F_VOID("update_priorities", rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::update_priorities)));

  ADD_CD_VALUE_UNI("is_open",          rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::is_open)));
  ADD_CD_VALUE_UNI("is_active",        rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::is_active)));
  ADD_CD_VALUE_UNI("is_hash_checked",  rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::is_hash_checked)));
  ADD_CD_VALUE_UNI("is_hash_checking", rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::is_hash_checking)));
  ADD_CD_VALUE_UNI("is_multi_file",    rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::is_multi_file)));

  // 0 - stopped
  // 1 - started
  ADD_CD_VARIABLE_VALUE("state", "rtorrent", "state");
  ADD_CD_VARIABLE_VALUE("complete", "rtorrent", "complete");

  // 0 off
  // 1 scheduled, being controlled by a download scheduler. Includes a priority.
  // 3 forced off
  // 2 forced on
  ADD_CD_VARIABLE_VALUE("mode", "rtorrent", "mode");

  // 0 - Not hashing
  // 1 - Normal hashing
  // 2 - Download finished, hashing
  ADD_CD_VARIABLE_VALUE("hashing", "rtorrent", "hashing");
  ADD_CD_VARIABLE_STRING("tied_to_file", "rtorrent", "tied_to_file");

  // The "state_changed" variable is required to be a valid unix time
  // value, it indicates the last time the torrent changed its state,
  // resume/pause.
  ADD_CD_VARIABLE_VALUE("state_changed", "rtorrent", "state_changed");
  ADD_CD_VARIABLE_VALUE_PUBLIC("ignore_commands", "rtorrent", "ignore_commands");

  ADD_CD_STRING_BI("connection_current", std::ptr_fun(&apply_d_connection_type), std::ptr_fun(&retrieve_d_connection_type));

  add_copy_to_download("get_connection_leech", "d.get_connection_leech");
  add_copy_to_download("set_connection_leech", "d.set_connection_leech");
  add_copy_to_download("get_connection_seed", "d.get_connection_seed");
  add_copy_to_download("set_connection_seed", "d.set_connection_seed");

  ADD_CD_VALUE_MEM_BI("max_file_size", &core::Download::file_list, &torrent::FileList::set_max_file_size, &torrent::FileList::max_file_size);

  // Deprecated.
  ADD_CD_VALUE_MEM_BI("min_peers",     &core::Download::download, &torrent::Download::set_peers_min, &torrent::Download::peers_min);
  ADD_CD_VALUE_MEM_BI("max_peers",     &core::Download::download, &torrent::Download::set_peers_max, &torrent::Download::peers_max);
  ADD_CD_VALUE_MEM_BI("max_uploads",   &core::Download::download, &torrent::Download::set_uploads_max, &torrent::Download::uploads_max);

  ADD_CD_VALUE_MEM_BI("peers_min",        &core::Download::download, &torrent::Download::set_peers_min, &torrent::Download::peers_min);
  ADD_CD_VALUE_MEM_BI("peers_max",        &core::Download::download, &torrent::Download::set_peers_max, &torrent::Download::peers_max);
  ADD_CD_VALUE_MEM_BI("uploads_max",      &core::Download::download, &torrent::Download::set_uploads_max, &torrent::Download::uploads_max);
  ADD_CD_VALUE_UNI("peers_connected",     rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::peers_connected)));
  ADD_CD_VALUE_UNI("peers_not_connected", rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::peers_not_connected)));
  ADD_CD_VALUE_UNI("peers_complete",      rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::peers_complete)));
  ADD_CD_VALUE_UNI("peers_accounted",     rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::peers_accounted)));

  ADD_CD_VALUE_MEM_UNI("up_rate",      &torrent::Download::mutable_up_rate, &torrent::Rate::rate);
  ADD_CD_VALUE_MEM_UNI("up_total",     &torrent::Download::mutable_up_rate, &torrent::Rate::total);
  ADD_CD_VALUE_MEM_UNI("down_rate",    &torrent::Download::mutable_down_rate, &torrent::Rate::rate);
  ADD_CD_VALUE_MEM_UNI("down_total",   &torrent::Download::mutable_down_rate, &torrent::Rate::total);
  ADD_CD_VALUE_MEM_UNI("skip_rate",    &torrent::Download::mutable_skip_rate, &torrent::Rate::rate);
  ADD_CD_VALUE_MEM_UNI("skip_total",   &torrent::Download::mutable_skip_rate, &torrent::Rate::total);

  ADD_CD_VALUE_UNI("bytes_done",       rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::bytes_done)));
  ADD_CD_VALUE_UNI("ratio",            std::ptr_fun(&apply_d_ratio));
  ADD_CD_VALUE_UNI("chunks_hashed",    rak::on(std::mem_fun(&core::Download::download), std::mem_fun(&torrent::Download::chunks_hashed)));
  ADD_CD_VALUE_UNI("free_diskspace",   rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::free_diskspace)));

  ADD_CD_VALUE_UNI("size_files",       rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::size_files)));
  ADD_CD_VALUE_UNI("size_bytes",       rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::size_bytes)));
  ADD_CD_VALUE_UNI("size_chunks",      rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::size_chunks)));

  ADD_CD_VALUE_UNI("completed_bytes",  rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::completed_bytes)));
  ADD_CD_VALUE_UNI("completed_chunks", rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::completed_chunks)));
  ADD_CD_VALUE_UNI("left_bytes",       rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::left_bytes)));

  ADD_CD_VALUE_UNI("chunk_size",       rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::chunk_size)));

  ADD_CD_VALUE_MEM_BI("tracker_numwant", &core::Download::tracker_list, &torrent::TrackerList::set_numwant, &torrent::TrackerList::numwant);
  ADD_CD_VALUE_UNI("tracker_focus",      rak::on(std::mem_fun(&core::Download::tracker_list), std::mem_fun(&torrent::TrackerList::focus)));
  ADD_CD_VALUE_UNI("tracker_size",       rak::on(std::mem_fun(&core::Download::tracker_list), std::mem_fun(&torrent::TrackerList::size)));

  ADD_CD_STRING_BI("directory",        std::mem_fun(&core::Download::set_root_directory), rak::on(std::mem_fun(&core::Download::file_list), std::mem_fun(&torrent::FileList::root_dir)));
  ADD_CD_VALUE_BI("priority",          std::mem_fun(&core::Download::set_priority), std::mem_fun(&core::Download::priority));
  ADD_CD_STRING_UNI("priority_str",    std::ptr_fun(&retrieve_d_priority_str));
}