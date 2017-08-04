{
    len = snprintf(ptr, left, " libidn/%s", stringprep_check_version(NULL));
    left -= len;
    ptr += len;
  }