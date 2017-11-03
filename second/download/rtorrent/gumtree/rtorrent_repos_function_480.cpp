Scheduler::size_type
Scheduler::active() const {
  return std::count_if(m_view->begin_visible(), m_view->end_visible(), std::mem_fun(&Download::is_active));
}