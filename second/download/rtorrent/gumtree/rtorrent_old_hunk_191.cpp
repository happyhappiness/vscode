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

int
WindowPeerList::done_percentage(torrent::Peer& p) {
  int chunks = m_download->download()->chunks_total();

  return chunks ? (100 * p.chunks_done()) / chunks : 0;
}

}
