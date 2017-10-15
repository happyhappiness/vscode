    m_canvas->print(x, y, "%.1f", (double)p.get_rate_down() / 1024);
    x += 7;

    m_canvas->print(x, y, "%.1f", (double)p.get_rate_peer() / 1024);
    x += 7;

    m_canvas->print(x, y, "%c%c/%c%c",
		    p.get_remote_choked() ? 'c' : 'u',
		    p.get_remote_interested() ? 'i' : 'n',
		    p.get_local_choked() ? 'c' : 'u',
		    p.get_local_interested() ? 'i' : 'n');
    x += 7;

    m_canvas->print(x, y, "%i/%i",
		    p.get_outgoing_queue_size(),
		    p.get_incoming_queue_size());
    x += 6;
