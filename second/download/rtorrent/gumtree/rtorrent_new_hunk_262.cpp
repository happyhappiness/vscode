                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");

    } else if (itr.is_leaving()) {
      m_canvas->print(16 + itr.depth() - 1, pos, "/");

    } else if (itr.is_file()) {
      char buffer[std::max<unsigned int>(m_canvas->width() + 1, 256)];
      Canvas::attributes_list attributes;

      torrent::File* e = *itr;

      const char* priority;

      switch (e->priority()) {
      case torrent::PRIORITY_OFF:    priority = "off"; break;
      case torrent::PRIORITY_NORMAL: priority = "   "; break;
      case torrent::PRIORITY_HIGH:   priority = "hig"; break;
      default: priority = "BUG"; break;
      };

      sprintf(buffer, "%3d %s ", done_percentage(e), priority);

      int64_t val = e->size_bytes();

      if (val < (int64_t(1000) << 20))
        sprintf(buffer + 8, "%5.1f M", (double)val / (int64_t(1) << 20));
      else if (val < (int64_t(1000) << 30))
        sprintf(buffer + 8, "%5.1f G", (double)val / (int64_t(1) << 30));
      else
        sprintf(buffer + 8, "%5.1f T", (double)val / (int64_t(1) << 40));

      std::fill_n(buffer + 15, 64, ' ');

      int first = 16 + std::min<unsigned int>(itr.depth(), 8);
      int last = std::max<unsigned int>(m_canvas->width() + 1, 16 + 12);

      snprintf(buffer + first, last - first, "| %s",
               itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");

      m_canvas->print_attributes(0, pos, buffer, buffer + std::strlen(buffer), &attributes);

    } else {
      m_canvas->print(0, pos, "BORK BORK");
    }

    if (itr == m_element->selected())
