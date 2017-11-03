void
WindowHttpQueue::receive_erase(core::CurlGet* h) {
  Container::iterator itr = std::find_if(m_container.begin(), m_container.end(), rak::equal(h, std::mem_fun_ref(&Node::get_http)));

  if (itr == m_container.end())
    throw std::logic_error("WindowHttpQueue::receive_erase(...) tried to remove an object we don't have");

  itr->m_http = NULL;
  itr->m_timer = cachedTime + rak::timer::from_seconds(1);

  mark_dirty();
}