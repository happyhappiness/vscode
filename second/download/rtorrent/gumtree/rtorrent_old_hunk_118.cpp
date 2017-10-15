
void
WindowFileList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  if (m_download->get_download().size_file_entries() == 0 ||
      m_canvas->get_height() < 2)
    return;

  int pos = 0;

  m_canvas->print( 2, pos, "File");
  m_canvas->print(55, pos, "Size");
