      case torrent::PRIORITY_OFF:    priority = "off"; break;
      case torrent::PRIORITY_NORMAL: priority = "   "; break;
      case torrent::PRIORITY_HIGH:   priority = "hig"; break;
      default: priority = "BUG"; break;
      };

      m_canvas->print(0, pos, "%3d %s ", done_percentage(e), priority);

      int64_t val = e->size_bytes();

      if (val < (int64_t(1000) << 20))
        m_canvas->print(8, pos, "%5.1f M", (double)val / (int64_t(1) << 20));
      else if (val < (int64_t(1000) << 30))
