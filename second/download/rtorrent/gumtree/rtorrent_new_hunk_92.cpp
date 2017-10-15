		  !torrent::bind_address().empty() ? ("  Bind: " + torrent::bind_address()).c_str() : "");

#ifndef USE_EXTRA_DEBUG
  pos = snprintf(buf, 128, "[U %i/%i][S %i/%i/%i][F %i/%i]",
#else
  pos = snprintf(buf, 128, "%i [U %i/%i][S %i/%i/%i][F %i/%i]",
		 (int)(m_control->tick() - m_lastTick),
#endif
		 torrent::currently_unchoked(),
		 torrent::max_unchoked(),
		 torrent::total_handshakes(),
		 torrent::open_sockets(),
		 torrent::max_open_sockets(),
		 torrent::open_files(),
		 torrent::max_open_files());

  m_canvas->print(m_canvas->get_width() - pos, 0, "%s", buf);

  m_lastTick = m_control->tick();
}

}
