void
initialize_command_local() {
  torrent::ChunkManager* chunkManager = torrent::chunk_manager();
  core::DownloadList*    dList = control->core()->download_list();
  core::DownloadStore*   dStore = control->core()->download_store();

  ADD_VARIABLE_C_STRING("client_version",  PACKAGE_VERSION);
  ADD_VARIABLE_C_STRING("library_version", torrent::version());

  ADD_VARIABLE_VALUE("max_file_size", -1);
  ADD_VARIABLE_VALUE("split_file_size", -1);
  ADD_VARIABLE_STRING("split_suffix", ".part");

  ADD_COMMAND_VALUE_TRI("max_memory_usage",      rak::make_mem_fun(chunkManager, &CM_t::set_max_memory_usage), rak::make_mem_fun(chunkManager, &CM_t::max_memory_usage));
  ADD_COMMAND_VALUE_TRI("safe_sync",             rak::make_mem_fun(chunkManager, &CM_t::set_safe_sync), rak::make_mem_fun(chunkManager, &CM_t::safe_sync));
  ADD_COMMAND_VALUE_TRI("timeout_sync",          rak::make_mem_fun(chunkManager, &CM_t::set_timeout_sync), rak::make_mem_fun(chunkManager, &CM_t::timeout_sync));
  ADD_COMMAND_VALUE_TRI("timeout_safe_sync",     rak::make_mem_fun(chunkManager, &CM_t::set_timeout_safe_sync), rak::make_mem_fun(chunkManager, &CM_t::timeout_safe_sync));

  ADD_COMMAND_VALUE_TRI("preload_type",          rak::make_mem_fun(chunkManager, &CM_t::set_preload_type), rak::make_mem_fun(chunkManager, &CM_t::preload_type));
  ADD_COMMAND_VALUE_TRI("preload_min_size",      rak::make_mem_fun(chunkManager, &CM_t::set_preload_min_size), rak::make_mem_fun(chunkManager, &CM_t::preload_min_size));
  ADD_COMMAND_VALUE_TRI_KB("preload_required_rate", rak::make_mem_fun(chunkManager, &CM_t::set_preload_required_rate), rak::make_mem_fun(chunkManager, &CM_t::preload_required_rate));

  ADD_VARIABLE_STRING("directory", "./");

  ADD_COMMAND_STRING_TRI("session",            rak::make_mem_fun(dStore, &core::DownloadStore::set_path), rak::make_mem_fun(dStore, &core::DownloadStore::path));
  ADD_COMMAND_VOID("session_save",             rak::make_mem_fun(dList, &core::DownloadList::session_save));

  ADD_COMMAND_VALUE_TRI_OCT("umask",           rak::make_mem_fun(control, &Control::set_umask), rak::make_mem_fun(control, &Control::umask));
  ADD_COMMAND_STRING_TRI("working_directory",  rak::make_mem_fun(control, &Control::set_working_directory), rak::make_mem_fun(control, &Control::working_directory));

  ADD_COMMAND_LIST("execute",             rak::bind2_mem_fn(&rpc::execFile, &rpc::ExecFile::execute_object, rpc::ExecFile::flag_throw | rpc::ExecFile::flag_expand_tilde));
  ADD_COMMAND_LIST("execute_nothrow",     rak::bind2_mem_fn(&rpc::execFile, &rpc::ExecFile::execute_object, rpc::ExecFile::flag_expand_tilde));
  ADD_COMMAND_LIST("execute_raw",         rak::bind2_mem_fn(&rpc::execFile, &rpc::ExecFile::execute_object, rpc::ExecFile::flag_throw));
  ADD_COMMAND_LIST("execute_raw_nothrow", rak::bind2_mem_fn(&rpc::execFile, &rpc::ExecFile::execute_object, 0));

  ADD_COMMAND_STRING_UN("execute_log",    std::ptr_fun(&apply_execute_log));
}