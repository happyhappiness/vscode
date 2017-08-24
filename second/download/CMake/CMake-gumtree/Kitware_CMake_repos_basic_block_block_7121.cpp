f(result != CURLE_OK) {
        *err = result;
        written = -1;
        break;
      }