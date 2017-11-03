void
Manager::schedule(Window* w, rak::timer t) {
  rak::priority_queue_erase(&m_scheduler, w->task_update());
  rak::priority_queue_insert(&m_scheduler, w->task_update(), t);
  schedule_update(50000);
}