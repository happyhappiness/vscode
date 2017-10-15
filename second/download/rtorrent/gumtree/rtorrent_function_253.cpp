void
WindowPeerList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(1)).round_seconds());
  m_canvas->erase();

  int x = 2;
  int y = 0;

  m_canvas->print(x, y, "IP");     x += 16;
  m_canvas->print(x, y, "UP");      x += 7;
  m_canvas->print(x, y, "DOWN");    x += 7;
  m_canvas->print(x, y, "PEER");    x += 7;
  m_canvas->print(x, y, "C/RE/LO"); x += 9;
  m_canvas->print(x, y, "QS");      x += 6;
  m_canvas->print(x, y, "DONE");    x += 6;
  m_canvas->print(x, y, "REQ");     x += 6;
  m_canvas->print(x, y, "SNUB");    x += 6;
  m_canvas->print(x, y, "FAILED");

  ++y;

  if (m_list->empty())
    return;

  typedef std::pair<PList::iterator, PList::iterator> Range;

  Range range = rak::advance_bidirectional(m_list->begin(),
                                           *m_focus != m_list->end() ? *m_focus : m_list->begin(),
                                           m_list->end(),
                                           m_canvas->height() - y);

  if (m_download->download()->chunks_total() <= 0)
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

    m_canvas->print(x, y, "%c/%c%c/%c%c",
                    p.is_incoming() ? 'r' : 'l',
                    p.is_remote_choked() ? 'c' : 'u',
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
    control->client_info()->print(buf, buf + 128, p.id().c_str());

    m_canvas->print(x, y, "%s", buf);

    ++y;
    ++range.first;
  }
}