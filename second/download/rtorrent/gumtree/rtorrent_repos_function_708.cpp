void
Manager::schedule_update(uint32_t minInterval) {
  if (m_scheduler.empty()) {
    rak::priority_queue_erase(&taskScheduler, &m_taskUpdate);
    return;
  }

  if (!m_taskUpdate.is_queued() || m_taskUpdate.time() > m_scheduler.top()->time()) {
    rak::priority_queue_erase(&taskScheduler, &m_taskUpdate);
    rak::priority_queue_insert(&taskScheduler, &m_taskUpdate, std::max(m_scheduler.top()->time(), m_timeLastUpdate + minInterval));
  }
}