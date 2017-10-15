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
  m_canvas->print(0, pos++, "Cmp Pri  Size   Filename");

  while (pos != m_canvas->height()) {
    iterator itr = entries[first];

    if (itr == iterator(fl->end()))
      break;

    if (itr.is_empty()) {
      m_canvas->print(16, pos, "EMPTY");

    } else if (itr.is_entering()) {
      m_canvas->print(16 + itr.depth(), pos, "\\ %s", 
                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");

    } else if (itr.is_leaving()) {
      m_canvas->print(16 + itr.depth() - 1, pos, "/");

    } else if (itr.is_file()) {
      torrent::File* e = *itr;

      const char* priority;

      switch (e->priority()) {
      case torrent::PRIORITY_OFF:    priority = "off"; break;
      case torrent::PRIORITY_NORMAL: priority = "   "; break;
      case torrent::PRIORITY_HIGH:   priority = "hig"; break;
      default: priority = "BUG"; break;
      };

      m_canvas->print(0, pos, "%3d %s", done_percentage(e), priority);

      int64_t val = e->size_bytes();

      if (val < (int64_t(1000) << 20))
        m_canvas->print(8, pos, "%5.1f M", (double)val / (int64_t(1) << 20));
      else if (val < (int64_t(1000) << 30))
        m_canvas->print(8, pos, "%5.1f G", (double)val / (int64_t(1) << 30));
      else
        m_canvas->print(8, pos, "%5.1f T", (double)val / (int64_t(1) << 40));

      m_canvas->print(16 + itr.depth(), pos, "| %s",
                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");

//       m_canvas->print(104, pos, "%i - %i %c%c %u %u",
//                       e->range().first,
//                       e->range().first != e->range().second ? (e->range().second - 1) : e->range().second,
//                       e->is_created() ? 'E' : 'M',
//                       e->is_correct_size() ? 'C' : 'W',
//                       e->match_depth_prev(),
//                       e->match_depth_next());

    } else {
      m_canvas->print(0, pos, "BORK BORK");
    }

    if (itr == m_element->selected())
      m_canvas->set_attr(0, pos, m_canvas->width(), is_focused() ? A_REVERSE : A_BOLD, COLOR_PAIR(0));

    pos++;
    first = (first + 1) % (m_canvas->height() - 1);
  }
}