		    p.is_remote_choked() ? 'c' : 'u',
		    p.is_remote_interested() ? 'i' : 'n',
		    p.is_local_choked() ? 'c' : 'u',
		    p.is_local_interested() ? 'i' : 'n');
    x += 9;

    m_canvas->print(x, y, "%i/%i",
		    p.outgoing_queue_size(),
		    p.incoming_queue_size());
    x += 6;

    m_canvas->print(x, y, "%3i", done_percentage(*range.first));
    x += 6;

    if (p.incoming_queue_size())
      m_canvas->print(x, y, "%i", p.incoming_queue(0)->index());

    x += 6;

    if (p.is_snubbed())
      m_canvas->print(x, y, "*");

    x += 5;

    char buf[128];
    control->client_info()->print(buf, buf + 128, p.id().c_str());

    m_canvas->print(x, y, "%s", buf);

