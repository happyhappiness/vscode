
  if (torrent::get_read_throttle() == 0)
    pos = snprintf(buf + pos, 128 - pos, "off");
  else
    pos = snprintf(buf + pos, 128 - pos, "%-3i", torrent::get_read_throttle() / 1024);

  m_canvas->print(0, 0, "Throttle U/D: %s  Listen: %s:%i%s  Handshakes: %i",
		  buf,
		  !torrent::get_ip().empty() ? torrent::get_ip().c_str() : "<default>",
		  (int)torrent::get_listen_port(),
		  !torrent::get_bind().empty() ? ("  Bind: " + torrent::get_bind()).c_str() : "",
		  torrent::get_total_handshakes());
}

