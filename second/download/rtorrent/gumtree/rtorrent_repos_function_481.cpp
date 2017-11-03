void
Scheduler::update() {
  size_type curActive = active();
  //  size_type curInactive = m_view->size() - curActive;

  // Hmm... Perhaps we should use a more complex sorting thingie.
  m_view->sort();

  // Just a hack for now, need to take into consideration how many
  // inactive we can switch with.
  size_type target = m_maxActive - std::min(m_cycle, m_maxActive);

  for (View::iterator itr = m_view->begin_visible(), last = m_view->end_visible(); curActive > target; ++itr) {
    if (itr == last)
      throw torrent::internal_error("Scheduler::update() loop bork.");

    if ((*itr)->is_active()) {
      m_downloadList->pause(*itr);
      --curActive;
    }      
  }

  m_view->sort();

  for (View::iterator itr = m_view->begin_visible(), last = m_view->end_visible(); curActive < m_maxActive; ++itr) {
    if (itr == last)
      throw torrent::internal_error("Scheduler::update() loop bork.");

    if (!(*itr)->is_active()) {
      m_downloadList->start_try(*itr);
      ++curActive;
    }      
  }
}