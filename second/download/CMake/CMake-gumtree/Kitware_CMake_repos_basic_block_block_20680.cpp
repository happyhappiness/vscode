(NULL == wcspbrk(source, L" \t\"")) {
    /* No quotation needed */
    wcsncpy(target, source, len);
    target += len;
    return target;
  }