(path.find(it->first) == 0) {
      path = path.replace(0, it->first.size(), it->second);
    }