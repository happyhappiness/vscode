void
ElementPeerList::receive_peer_connected(torrent::Peer p) {
  m_list.push_back(p);
}