
  m_lastDraw = utils::Timer::cache();

  m_canvas->erase();
  m_canvas->print(0, 0, "Throttle: %i Listen: %s:%i Handshakes: %i Select: %u",
		  (int)torrent::get(torrent::THROTTLE_ROOT_CONST_RATE) / 1024,
		  "",
		  (int)torrent::get(torrent::LISTEN_PORT),
		  (int)torrent::get(torrent::HANDSHAKES_TOTAL),
		  m_counter);
}

}
