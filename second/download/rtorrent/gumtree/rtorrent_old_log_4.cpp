m_canvas->print(0, pos++, "%c Torrent: Done %.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
		      itr == *m_focus ? '*' : ' ',
		      (double)itr->get_download().get_bytes_total() / (double)(1 << 20),
		      (double)itr->get_download().get_rate_up() / 1024.0,
		      (double)itr->get_download().get_rate_down() / 1024.0,
		      (double)itr->get_download().get_bytes_up() / (double)(1 << 20));