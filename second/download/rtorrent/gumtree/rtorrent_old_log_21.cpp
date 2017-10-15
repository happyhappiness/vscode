m_canvas->print(x, y, "%c%c/%c%c%c",
	     itr->get_remote_choked() ? 'c' : 'u',
	     itr->get_remote_interested() ? 'i' : 'n',
	     itr->get_local_choked() ? 'c' : 'u',
	     itr->get_local_interested() ? 'i' : 'n',
	     itr->get_choke_delayed() ? 'd' : ' ');