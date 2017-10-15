  m_list(l),
  m_focus(f) {
}

void
WindowPeerInfo::redraw() {
  m_slotSchedule(this, (cachedTime + 1000000).round_seconds());
  m_canvas->erase();

  int y = 0;
  torrent::Download d = m_download->get_download();

  m_canvas->print(0, y++, "Hash:    %s", rak::transform_hex(d.info_hash()).c_str());
  m_canvas->print(0, y++, "Id:      %s", rak::copy_escape_html(d.local_id()).c_str());
  m_canvas->print(0, y++, "Chunks:  %u / %u * %u",
		  d.chunks_done(),
		  d.chunks_total(),
		  d.chunks_size());

  char buffer[32], *position;
