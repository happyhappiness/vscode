void
Control::handle_shutdown() {
  if (!m_shutdownQuick) {
    torrent::connection_manager()->listen_close();
    m_core->shutdown(false);

    if (!m_taskShutdown.is_queued())
      priority_queue_insert(&taskScheduler, &m_taskShutdown, cachedTime + rak::timer::from_seconds(5));

  } else {
    m_core->shutdown(true);
  }

  m_shutdownQuick = true;
  m_shutdownReceived = false;
}