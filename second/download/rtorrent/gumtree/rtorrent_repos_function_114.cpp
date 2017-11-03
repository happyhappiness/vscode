void
Control::initialize() {
  display::Canvas::initialize();
  display::Window::slot_schedule(rak::make_mem_fun(m_display, &display::Manager::schedule));
  display::Window::slot_unschedule(rak::make_mem_fun(m_display, &display::Manager::unschedule));
  display::Window::slot_adjust(rak::make_mem_fun(m_display, &display::Manager::adjust_layout));

  m_core->get_poll_manager()->get_http_stack()->set_user_agent(USER_AGENT);

  m_core->initialize_second();
  m_core->listen_open();
  m_core->download_store()->enable(rpc::call_command_value("get_session_lock"));

  m_core->set_hashing_view(*m_viewManager->find_throw("hashing"));
  m_scheduler->set_view(*m_viewManager->find_throw("scheduler"));

  m_ui->init(this);

  m_inputStdin->insert(m_core->get_poll_manager()->get_torrent_poll());
}