(cc = 2; cc < expr.size(); cc++) {
        if (expr[cc] == '/') {
          cnt++;
          if (cnt == 2) {
            break;
          }
        }
      }