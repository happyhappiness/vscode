m_canvas->print(0, 0, "Torrent: %.1f / %.1f MiB Rate: %5.1f / %5.1f KiB Uploaded: %.1f MiB",
		    (double)m_download->get_download().get_bytes_done() / (double)(1 << 20),
		    (double)m_download->get_download().get_bytes_total() / (double)(1 << 20),
		    (double)m_download->get_download().get_rate_up() / 1024.0,
		    (double)m_download->get_download().get_rate_down() / 1024.0,
		    (double)m_download->get_download().get_bytes_up() / (double)(1 << 20));