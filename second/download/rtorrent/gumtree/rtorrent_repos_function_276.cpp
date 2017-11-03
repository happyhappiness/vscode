void
CommandSchedulerItem::enable(rak::timer t) {
  if (t == rak::timer())
    throw torrent::internal_error("CommandSchedulerItem::enable() t == rak::timer().");

  if (is_queued())
    disable();

  // If 'first' is zero then we execute the task
  // immediately. ''interval()'' will not return zero so we never end
  // up in an infinit loop.
  m_timeScheduled = t;
  priority_queue_insert(&taskScheduler, &m_task, t);
}