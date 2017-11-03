void
ElementPeerList::receive_next() {
  if (m_listItr != m_list.end())
    ++m_listItr;
  else
    m_listItr = m_list.begin();

  update_itr();
}