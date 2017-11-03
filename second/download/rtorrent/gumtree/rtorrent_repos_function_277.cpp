void
CommandSchedulerItem::disable() {
  m_timeScheduled = rak::timer();
  priority_queue_erase(&taskScheduler, &m_task);
}