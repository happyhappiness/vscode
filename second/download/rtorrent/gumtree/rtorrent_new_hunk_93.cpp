  Window(new Canvas, false, 1),
  m_title(s) {
}

void
WindowTitle::redraw() {
  m_slotSchedule(this, (cachedTime + 1000000).round_seconds());
  m_canvas->erase();

  m_canvas->print(std::max(0, (m_canvas->get_width() - (int)m_title.size()) / 2 - 4), 0,
		  "*** %s ***", m_title.c_str());
}

