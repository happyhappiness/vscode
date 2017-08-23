{
    snprintf(buf, sizeof(buf), "CHARSET=cp%u", cp);
    putenv(buf);
  }