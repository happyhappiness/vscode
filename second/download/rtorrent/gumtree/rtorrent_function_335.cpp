void
WindowFileList::redraw() {
  m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(10)).round_seconds());
  m_canvas->erase();

  torrent::FileList* fl = m_element->download()->download()->file_list();

  if (fl->size_files() == 0 || m_canvas->height() < 2)
    return;

  iterator entries[m_canvas->height() - 1];

  unsigned int last = 0;

  for (iterator itr = m_element->selected(); last != m_canvas->height() - 1; ) {
    if (m_element->is_collapsed())
      itr.forward_current_depth();
    else
      ++itr;

    entries[last++] = itr;

    if (itr == iterator(fl->end()))
      break;
  }

  unsigned int first = m_canvas->height() - 1;

  for (iterator itr = m_element->selected(); first >= last || first > (m_canvas->height() - 1) / 2; ) {
    entries[--first] = itr;

    if (itr == iterator(fl->begin()))
      break;

    if (m_element->is_collapsed())
      itr.backward_current_depth();
    else
      --itr;
  }

  unsigned int pos = 0;
  int filenameWidth = m_canvas->width() - 16;

  m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");

  while (pos != m_canvas->height()) {
    iterator itr = entries[first];

    if (itr == iterator(fl->end()))
      break;

    m_canvas->set_default_attributes(itr == m_element->selected() ? is_focused() ? A_REVERSE : A_BOLD : A_NORMAL);

    if (itr.is_empty()) {
      m_canvas->print(0, pos, "%*c%-*s", 16, ' ', filenameWidth, "EMPTY");

    } else if (itr.is_entering()) {
      m_canvas->print(0, pos, "%*c %ls", 16 + itr.depth(), '\\',
                      itr.depth() < (*itr)->path()->size() ? wstring_width((*itr)->path()->at(itr.depth()), filenameWidth - itr.depth() - 1).c_str() : L"UNKNOWN");

    } else if (itr.is_leaving()) {
      m_canvas->print(0, pos, "%*c %-*s", 16 + (itr.depth() - 1), '/', filenameWidth - (itr.depth() - 1), "");

    } else if (itr.is_file()) {
      torrent::File* e = *itr;

      const char* priority;

      switch (e->priority()) {
      case torrent::PRIORITY_OFF:    priority = "off"; break;
      case torrent::PRIORITY_NORMAL: priority = "   "; break;
      case torrent::PRIORITY_HIGH:   priority = "hig"; break;
      default: priority = "BUG"; break;
      };

      m_canvas->print(0, pos, "%3d %s ", done_percentage(e), priority);

      int64_t val = e->size_bytes();

      if (val < (int64_t(1000) << 10))
        m_canvas->print(8, pos, "%5.1f K", (double)val / (int64_t(1) << 10));
      else if (val < (int64_t(1000) << 20))
        m_canvas->print(8, pos, "%5.1f M", (double)val / (int64_t(1) << 20));
      else if (val < (int64_t(1000) << 30))
        m_canvas->print(8, pos, "%5.1f G", (double)val / (int64_t(1) << 30));
      else
        m_canvas->print(8, pos, "%5.1f T", (double)val / (int64_t(1) << 40));

      m_canvas->print(15, pos, "%*c %ls", 1 + itr.depth(), '|',
                      itr.depth() < (*itr)->path()->size() ? wstring_width((*itr)->path()->at(itr.depth()), filenameWidth - itr.depth() - 1).c_str() : L"UNKNOWN");

    } else {
      m_canvas->print(0, pos, "BORK BORK");
    }
    m_canvas->set_default_attributes(A_NORMAL);

    pos++;
    first = (first + 1) % (m_canvas->height() - 1);
  }
}