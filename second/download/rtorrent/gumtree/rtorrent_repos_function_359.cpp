void
ElementPeerList::receive_prev() {
  if (m_listItr != m_list.begin())
    --m_listItr;
  else
    m_listItr = m_list.end();

  update_itr();
}