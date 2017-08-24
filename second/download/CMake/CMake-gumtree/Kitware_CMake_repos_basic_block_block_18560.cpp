e(n > 0) {
    *p = strchr(*p, '\n');
    if (!p)
      return lines;

    (*p)++;
    n--;
    lines++;
  }