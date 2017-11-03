void
Manager::unschedule(Window* w) {
  rak::priority_queue_erase(&m_scheduler, w->task_update());
  schedule_update(50000);
}