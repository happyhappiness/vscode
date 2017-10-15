snprintf(buffer + first, last - first, "| %s",
               itr.depth() < (*itr)->path()->size() ? (*itr)->path()->at(itr.depth()).c_str() : "UNKNOWN");