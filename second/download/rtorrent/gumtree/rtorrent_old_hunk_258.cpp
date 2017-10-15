                                           m_canvas->height() - y);

  if (m_download->download()->file_list()->size_chunks() <= 0)
    throw std::logic_error("WindowPeerList::redraw() m_slotChunksTotal() returned invalid value");

  while (range.first != range.second) {
    torrent::Peer& p = *range.first;

    x = 0;

    m_canvas->print(x, y, "%c %s",
                    range.first == *m_focus ? '*' : ' ',
                    rak::socket_address::cast_from(p.address())->address_str().c_str());
    x += 18;

    m_canvas->print(x, y, "%.1f", (double)p.up_rate()->rate() / 1024); x += 7;
    m_canvas->print(x, y, "%.1f", (double)p.down_rate()->rate() / 1024); x += 7;
    m_canvas->print(x, y, "%.1f", (double)p.peer_rate()->rate() / 1024); x += 7;

    char remoteChoked;

    if (!p.is_remote_choked_limited())
      remoteChoked = 'U';
    else if (p.is_remote_queued())
      remoteChoked = 'Q';
    else
      remoteChoked = 'C';

    m_canvas->print(x, y, "%c/%c%c/%c%c",
                    p.is_encrypted() ? (p.is_incoming() ? 'R' : 'L') : (p.is_incoming() ? 'r' : 'l'),
                    p.is_remote_choked() ? std::tolower(remoteChoked) : remoteChoked,

                    p.is_remote_interested() ? 'i' : 'n',
                    p.is_local_choked() ? 'c' : 'u',
                    p.is_local_interested() ? 'i' : 'n');
    x += 9;

    m_canvas->print(x, y, "%i/%i", p.outgoing_queue_size(), p.incoming_queue_size());
    x += 6;

    m_canvas->print(x, y, "%3i", done_percentage(*range.first));
    x += 6;

    const torrent::BlockTransfer* transfer = p.transfer();

    if (transfer != NULL)
      m_canvas->print(x, y, "%i", transfer->index());

    x += 6;

    if (p.is_snubbed())
      m_canvas->print(x, y, "*");

    x += 6;

    if (p.failed_counter() != 0)
      m_canvas->print(x, y, "%u", p.failed_counter());

    x += 7;

    char buf[128];
    print_client_version(buf, buf + 128, p.info()->client_info());

    m_canvas->print(x, y, "%s", buf);

    ++y;
    ++range.first;
  }
}

int
WindowPeerList::done_percentage(torrent::Peer& p) {
  int chunks = m_download->download()->file_list()->size_chunks();

  return chunks ? (100 * p.chunks_done()) / chunks : 0;
}

}
