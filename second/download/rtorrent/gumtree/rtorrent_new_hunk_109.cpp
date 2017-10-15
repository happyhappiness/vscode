  m_focus(focus) {
}

void
WindowTrackerList::redraw() {
  // TODO: Make this depend on tracker signal.
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  int pos = 0;

  m_canvas->print( 2, pos, "Trackers:");

