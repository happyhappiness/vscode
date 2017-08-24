(expr[0] == '/' && expr[1] == '/') {
      int cnt = 0;
      for (cc = 2; cc < expr.size(); cc++) {
        if (expr[cc] == '/') {
          cnt++;
          if (cnt == 2) {
            break;
          }
        }
      }
      skip = int(cc + 1);
    } else
#endif
      // Handle drive letters on Windows
      if (expr[1] == ':' && expr[0] != '/') {
      skip = 2;
    }