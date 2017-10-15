
    default:
      priority = "BUG";
      break;
    };

    m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d  %9s",
		    range.first == *m_focus ? '*' : ' ',
		    path.c_str(),
		    (double)e.size_bytes() / (double)(1 << 20),
		    priority.c_str(),
		    done_percentage(e),
		    e.path()->encoding().c_str());

    m_canvas->print(84, pos, "%i - %i",
		    e.chunk_begin(),
		    e.chunk_end());

    ++range.first;
    ++pos;
  }

}

int
WindowFileList::done_percentage(torrent::Entry& e) {
  int chunks = e.chunk_end() - e.chunk_begin();

  return chunks ? (e.completed_chunks() * 100) / chunks : 100;
}

}
