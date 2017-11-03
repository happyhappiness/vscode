rak::timer
CommandSchedulerItem::next_time_scheduled() const {
  if (m_interval == 0)
    return rak::timer();

  if (m_timeScheduled == rak::timer())
    throw torrent::internal_error("CommandSchedulerItem::next_time_scheduled() m_timeScheduled == rak::timer().");

  rak::timer next = m_timeScheduled;

  // This should be done in a non-looping manner.
  do {
    next += rak::timer::from_seconds(m_interval);
  } while (next <= cachedTime.round_seconds());

  return next;
}