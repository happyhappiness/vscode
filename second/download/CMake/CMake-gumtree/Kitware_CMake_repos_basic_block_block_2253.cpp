(*i == up) {
      if (out_components.size() > 1) {
        out_components.resize(out_components.size() - 1);
      }
    } else if (!i->empty() && *i != cur) {
      out_components.push_back(*i);
    }