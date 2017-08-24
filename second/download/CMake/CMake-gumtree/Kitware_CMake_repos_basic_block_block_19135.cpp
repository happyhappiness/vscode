(i = 1; i <= 22; i++) {
    s = strchr(s + 1, ' ');
    if (s == NULL)
      goto err;
  }