void
Control::cleanup() {
  delete m_scgi;    m_scgi = NULL;
  rpc::xmlrpc.cleanup();

  priority_queue_erase(&taskScheduler, &m_taskShutdown);

  m_inputStdin->remove(m_core->get_poll_manager()->get_torrent_poll());

  m_core->download_store()->disable();

  m_ui->cleanup();
  m_core->cleanup();
  
  display::Canvas::erase_std();
  display::Canvas::refresh_std();
  display::Canvas::do_update();
  display::Canvas::cleanup();
}