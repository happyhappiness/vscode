void
initialize_command_network() {
  torrent::ConnectionManager* cm = torrent::connection_manager();
  core::CurlStack* httpStack = control->core()->get_poll_manager()->get_http_stack();

  ADD_VARIABLE_BOOL("use_udp_trackers", true);

  ADD_VARIABLE_BOOL("port_open", true);
  ADD_VARIABLE_BOOL("port_random", true);
  ADD_VARIABLE_STRING("port_range", "6881-6999");

  ADD_VARIABLE_STRING("connection_leech", "leech");
  ADD_VARIABLE_STRING("connection_seed", "seed");

  ADD_VARIABLE_VALUE("min_peers", 40);
  ADD_VARIABLE_VALUE("max_peers", 100);
  ADD_VARIABLE_VALUE("min_peers_seed", -1);
  ADD_VARIABLE_VALUE("max_peers_seed", -1);

  ADD_VARIABLE_VALUE("max_uploads", 15);

  ADD_VARIABLE_VALUE("max_uploads_div",      1);
  ADD_VARIABLE_VALUE("max_uploads_global",   0);
  ADD_VARIABLE_VALUE("max_downloads_div",    1);
  ADD_VARIABLE_VALUE("max_downloads_global", 0);

//   ADD_COMMAND_VALUE_TRI("max_uploads_global",   rak::make_mem_fun(control->ui(), &ui::Root::set_max_uploads_global), rak::make_mem_fun(control->ui(), &ui::Root::max_uploads_global));
//   ADD_COMMAND_VALUE_TRI("max_downloads_global", rak::make_mem_fun(control->ui(), &ui::Root::set_max_downloads_global), rak::make_mem_fun(control->ui(), &ui::Root::max_downloads_global));

  ADD_COMMAND_VALUE_TRI_KB("download_rate",     rak::make_mem_fun(control->ui(), &ui::Root::set_down_throttle_i64), rak::ptr_fun(&torrent::down_throttle));
  ADD_COMMAND_VALUE_TRI_KB("upload_rate",       rak::make_mem_fun(control->ui(), &ui::Root::set_up_throttle_i64), rak::ptr_fun(&torrent::up_throttle));

  ADD_VARIABLE_VALUE("tracker_numwant", -1);

  ADD_COMMAND_LIST("encryption",          rak::ptr_fn(&apply_encryption));

  ADD_COMMAND_STRING("tos",               rak::ptr_fn(&apply_tos));

  ADD_COMMAND_STRING_TRI("bind",          rak::make_mem_fun(control->core(), &core::Manager::set_bind_address), rak::make_mem_fun(control->core(), &core::Manager::bind_address));
  ADD_COMMAND_STRING_TRI("ip",            rak::make_mem_fun(control->core(), &core::Manager::set_local_address), rak::make_mem_fun(control->core(), &core::Manager::local_address));
  ADD_COMMAND_STRING_TRI("proxy_address", rak::make_mem_fun(control->core(), &core::Manager::set_proxy_address), rak::make_mem_fun(control->core(), &core::Manager::proxy_address));
  ADD_COMMAND_STRING_TRI("http_proxy",    rak::make_mem_fun(httpStack, &core::CurlStack::set_http_proxy), rak::make_mem_fun(httpStack, &core::CurlStack::http_proxy));
  ADD_COMMAND_STRING_TRI("http_capath",   rak::make_mem_fun(httpStack, &core::CurlStack::set_http_capath), rak::make_mem_fun(httpStack, &core::CurlStack::http_capath));
  ADD_COMMAND_STRING_TRI("http_cacert",   rak::make_mem_fun(httpStack, &core::CurlStack::set_http_cacert), rak::make_mem_fun(httpStack, &core::CurlStack::http_cacert));

  ADD_COMMAND_VALUE_TRI("send_buffer_size",    rak::make_mem_fun(cm, &torrent::ConnectionManager::set_send_buffer_size), rak::make_mem_fun(cm, &torrent::ConnectionManager::send_buffer_size));
  ADD_COMMAND_VALUE_TRI("receive_buffer_size", rak::make_mem_fun(cm, &torrent::ConnectionManager::set_receive_buffer_size), rak::make_mem_fun(cm, &torrent::ConnectionManager::receive_buffer_size));

  ADD_COMMAND_VALUE_TRI("hash_max_tries",       std::ptr_fun(&torrent::set_hash_max_tries), rak::ptr_fun(&torrent::hash_max_tries));
  ADD_COMMAND_VALUE_TRI("max_open_files",       std::ptr_fun(&torrent::set_max_open_files), rak::ptr_fun(&torrent::max_open_files));
  ADD_COMMAND_VALUE_TRI("max_open_sockets",     rak::make_mem_fun(cm, &torrent::ConnectionManager::set_max_size), rak::make_mem_fun(cm, &torrent::ConnectionManager::max_size));
  ADD_COMMAND_VALUE_TRI("max_open_http",        rak::make_mem_fun(httpStack, &core::CurlStack::set_max_active), rak::make_mem_fun(httpStack, &core::CurlStack::max_active));

  ADD_COMMAND_STRING_UN("scgi_port",            rak::bind2nd(std::ptr_fun(&apply_scgi), 1));
  ADD_COMMAND_STRING_UN("scgi_local",           rak::bind2nd(std::ptr_fun(&apply_scgi), 2));
  ADD_VARIABLE_BOOL("scgi_dont_route", false);
  ADD_COMMAND_STRING_UN("xmlrpc_dialect",       std::ptr_fun(&apply_xmlrpc_dialect));

  ADD_COMMAND_VALUE_TRI("hash_read_ahead",      std::ptr_fun(&apply_hash_read_ahead), rak::ptr_fun(torrent::hash_read_ahead));
  ADD_COMMAND_VALUE_TRI("hash_interval",        std::ptr_fun(&apply_hash_interval), rak::ptr_fun(torrent::hash_interval));

  ADD_COMMAND_VALUE_UN("enable_trackers",       std::ptr_fun(&apply_enable_trackers));
  ADD_COMMAND_STRING_UN("encoding_list",        std::ptr_fun(&apply_encoding_list));

  // Not really network stuff:
  ADD_VARIABLE_BOOL("handshake_log", false);
  ADD_VARIABLE_STRING("tracker_dump", "");
}