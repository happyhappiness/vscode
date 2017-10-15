m_canvas->print(16 + itr.depth(), pos, "| %s",
                      itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");