
    m_canvas->print(x, y, "%.1f", (double)p->up_rate()->rate() / 1024); x += 7;
    m_canvas->print(x, y, "%.1f", (double)p->down_rate()->rate() / 1024); x += 7;
    m_canvas->print(x, y, "%.1f", (double)p->peer_rate()->rate() / 1024); x += 7;

    char remoteChoked;
    char peerType;

    if (!p->is_down_choked_limited())
      remoteChoked = 'U';
    else if (p->is_down_queued())
      remoteChoked = 'Q';
    else
      remoteChoked = 'C';

    if (p->peer_info()->is_blocked())
      peerType = 'u';
    else if (p->peer_info()->is_preferred())
      peerType = 'p';
    else 
      peerType = ' ';

    m_canvas->print(x, y, "%c%c/%c%c/%c%c",
                    p->is_encrypted() ? (p->is_incoming() ? 'R' : 'L') : (p->is_incoming() ? 'r' : 'l'),
                    peerType,
                    p->is_down_choked() ? std::tolower(remoteChoked) : remoteChoked,

                    p->is_down_interested() ? 'i' : 'n',
                    p->is_up_choked() ? 'c' : 'u',
                    p->is_up_interested() ? 'i' : 'n');
    x += 10;

    m_canvas->print(x, y, "%i/%i", p->outgoing_queue_size(), p->incoming_queue_size());
    x += 6;

    m_canvas->print(x, y, "%3i", done_percentage(*range.first));
    x += 6;
