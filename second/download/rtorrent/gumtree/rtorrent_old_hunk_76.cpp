
    default:
      priority = "BUG";
      break;
    };

    m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d",
		    range.first == *m_focus ? '*' : ' ',
		    path.c_str(),
		    (double)e.get_size() / (double)(1 << 20),
		    priority.c_str(),
		    done_percentage(e));

    ++range.first;
    ++pos;
  }

}

int
WindowFileList::done_percentage(torrent::Entry& e) {
  int chunks = e.get_chunk_end() - e.get_chunk_begin();

  return chunks ? (e.get_completed() * 100) / chunks : 100;
}

}
