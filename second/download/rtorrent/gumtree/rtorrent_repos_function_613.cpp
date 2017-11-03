void
WindowLog::receive_update() {
  if (!is_active())
    return;

  iterator itr = find_older();
  extent_type height = std::min(std::distance(m_log->begin(), itr), (std::iterator_traits<iterator>::difference_type)10);

  if (height != m_maxHeight) {
    m_minHeight = height != 0 ? 1 : 0;
    m_maxHeight = height;
    m_slotAdjust();

  } else {
    mark_dirty();
  }

  priority_queue_erase(&taskScheduler, &m_taskUpdate);

  if (height != 0)
    priority_queue_insert(&taskScheduler, &m_taskUpdate, (cachedTime + rak::timer::from_seconds(30)).round_seconds());
}