void
WindowHttpQueue::cleanup_list() {
  for (Container::iterator itr = m_container.begin(); itr != m_container.end();)
    if (itr->m_http == NULL && itr->m_timer < cachedTime)
      itr = m_container.erase(itr);
    else
      ++itr;

  // Bad, can't have this here as it is called from redraw().
  //   mark_dirty();
}