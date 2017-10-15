    x += 6;

    m_canvas->print(x, y, "%3i", done_percentage(*range.first));
    x += 6;

    if (p.incoming_queue_size())
      m_canvas->print(x, y, "%i", p.incoming_index(0));

    x += 6;

    if (p.is_snubbed())
      m_canvas->print(x, y, "*");

    ++y;
    ++range.first;
  }
}

int
WindowPeerList::done_percentage(torrent::Peer& p) {
  int chunks = m_download->get_download().chunks_total();

  return chunks ? (100 * p.chunks_done()) / chunks : 0;
}

}
