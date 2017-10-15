m_canvas->print(0, y++, "Rate: %5.1f/%5.1f KB Total: %.1f/%.1f MB",
		  (double)(*m_focus)->get_rate_up() / (double)(1 << 10),
		  (double)(*m_focus)->get_rate_down() / (double)(1 << 10),
		  (double)(*m_focus)->get_transfered_up() / (double)(1 << 20),
		  (double)(*m_focus)->get_transfered_down() / (double)(1 << 20));