m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->get_write_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_read_rate().rate() / (double)(1 << 10),
		  (double)(*m_focus)->get_write_rate().total() / (double)(1 << 20),
		  (double)(*m_focus)->get_read_rate().total() / (double)(1 << 20));