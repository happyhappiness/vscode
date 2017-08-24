(cc = strlen(nexec) - 1; cc > 0; cc--) {
    if (nexec[cc] == '/') {
      nexec[cc] = 0;
      if (cnt == 1) {
        break;
      }
      cnt++;
    }
  }