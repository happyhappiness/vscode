(size > 1 && *path.rbegin() == '/') {
      // if it is c:/ then do not remove the trailing slash
      if (!((size == 3 && pathCString[1] == ':'))) {
        path.resize(size - 1);
      }
    }