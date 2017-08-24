r(i = 0; i < 64; i++) {
    to[i] = *from;
    if(!*from++)
      break;
  }