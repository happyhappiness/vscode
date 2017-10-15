
void
WindowFileList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  torrent::FileList* fl = m_download->download()->file_list();

  if (fl->size_files() == 0 || m_canvas->height() < 2)
    return;

  unsigned int pos = 0;
  iterator itr = rak::advance_bidirectional<iterator>(iterator(fl->begin()), *m_selected, iterator(fl->end()), m_canvas->height() - 1).first;

  m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");

  while (pos != m_canvas->height() && itr != iterator(fl->end())) {
    if (itr.is_empty()) {
      m_canvas->print(16, pos, "EMPTY");

    } else if (itr.is_entering()) {
      m_canvas->print(16 + itr.depth(), pos, "\\ %s", 
                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");
