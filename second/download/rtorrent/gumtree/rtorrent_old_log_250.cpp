m_canvas->print(0, pos, "%c %s  %6.1f   %s   %3d  %9s",
                    range.first == *m_focus ? '*' : ' ',
                    path.c_str(),
                    (double)e.size_bytes() / (double)(1 << 20),
                    priority.c_str(),
                    done_percentage(e),
                    e.path()->encoding().c_str());