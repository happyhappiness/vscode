void
WindowHttpQueue::receive_insert(core::CurlGet* h) {
  m_container.push_back(Node(h, create_name(h)));

  if (!is_active()) {
    set_active(true);
    m_slotAdjust();
  }
  
  mark_dirty();
}