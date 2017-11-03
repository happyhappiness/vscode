void
ElementPeerList::receive_peer_disconnected(torrent::Peer p) {
  PList::iterator itr = std::find(m_list.begin(), m_list.end(), p);

  if (itr == m_list.end())
    throw torrent::internal_error("ElementPeerList::receive_peer_disconnected(...) itr == m_list.end().");

  if (itr == m_listItr)
    m_listItr = m_list.erase(itr);
  else
    m_list.erase(itr);

  update_itr();
}