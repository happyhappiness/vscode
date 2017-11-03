void
ElementPeerList::receive_disconnect_peer() {
  if (m_listItr == m_list.end())
    return;

  m_download->download()->disconnect_peer(*m_listItr);
}