int
WindowPeerList::done_percentage(torrent::Peer& p) {
  int chunks = m_download->download()->file_list()->size_chunks();

  return chunks ? (100 * p.chunks_done()) / chunks : 0;
}