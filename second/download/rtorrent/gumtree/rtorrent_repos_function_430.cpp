void
Download::set_priority(uint32_t p) {
  if (p >= 4)
    throw torrent::input_error("Priority out of range.");

  // Seeding torrents get half the priority of unfinished torrents.
  if (!is_done())
    torrent::download_set_priority(m_download, p * p * 2);
  else
    torrent::download_set_priority(m_download, p * p);

  bencode()->get_key("rtorrent").insert_key("priority", (int64_t)p);
}