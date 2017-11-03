void
Manager::initialize_second() {
  torrent::Http::set_factory(sigc::mem_fun(m_pollManager->get_http_stack(), &CurlStack::new_object));
  m_httpQueue->slot_factory(sigc::mem_fun(m_pollManager->get_http_stack(), &CurlStack::new_object));

  CurlStack::global_init();

  // Register slots to be called when a download is inserted/erased,
  // opened or closed.
  m_downloadList->slot_map_insert()["1_connect_network_log"]  = sigc::bind(sigc::ptr_fun(&connect_signal_network_log), sigc::mem_fun(m_logComplete, &Log::push_front));
  m_downloadList->slot_map_insert()["1_connect_storage_log"]  = sigc::bind(sigc::ptr_fun(&connect_signal_storage_log), sigc::mem_fun(m_logComplete, &Log::push_front));
  m_downloadList->slot_map_insert()["1_connect_tracker_dump"] = sigc::bind(sigc::ptr_fun(&connect_signal_tracker_dump), sigc::ptr_fun(&receive_tracker_dump));

  m_downloadList->slot_map_erase()["9_delete_tied"] = sigc::bind<0>(&rpc::call_command_d_v_void, "d.delete_tied");

  torrent::connection_manager()->set_signal_handshake_log(sigc::mem_fun(this, &Manager::handshake_log));
}