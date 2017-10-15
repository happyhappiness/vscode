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
