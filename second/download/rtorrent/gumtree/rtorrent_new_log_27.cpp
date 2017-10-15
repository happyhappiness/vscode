m_canvas->print(0, pos++, "%c Torrent: %6.1f / %6.1f MiB Rate:%5.1f /%5.1f KiB Uploaded: %.1f MiB",
		      range.first == *m_focus ? '*' : ' ',
		      (double)d.get_bytes_done() / (double)(1 << 20),
		      (double)d.get_bytes_total() / (double)(1 << 20),
		      (double)d.get_rate_up() / 1024.0,
		      (double)d.get_rate_down() / 1024.0,
		      (double)d.get_bytes_up() / (double)(1 << 20));