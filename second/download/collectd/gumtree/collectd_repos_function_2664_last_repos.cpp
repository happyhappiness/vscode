int strunescape(char *buf, size_t buf_len) {
  for (size_t i = 0; (i < buf_len) && (buf[i] != '\0'); ++i) {
    if (buf[i] != '\\')
      continue;

    if (((i + 1) >= buf_len) || (buf[i + 1] == 0)) {
      ERROR("string unescape: backslash found at end of string.");
      /* Ensure null-byte at the end of the buffer. */
      buf[i] = 0;
      return -1;
    }

    switch (buf[i + 1]) {
    case 't':
      buf[i] = '\t';
      break;
    case 'n':
      buf[i] = '\n';
      break;
    case 'r':
      buf[i] = '\r';
      break;
    default:
      buf[i] = buf[i + 1];
      break;
    }

    /* Move everything after the position one position to the left.
     * Add a null-byte as last character in the buffer. */
    memmove(buf + i + 1, buf + i + 2, buf_len - i - 2);
    buf[buf_len - 1] = 0;
  }
  return 0;
}