void
ElementPeerList::receive_snub_peer() {
  if (m_listItr == m_list.end())
    return;

  m_listItr->set_snubbed(!m_listItr->is_snubbed());

  update_itr();
}