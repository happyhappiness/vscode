static void nreftostr(uint32_t nrefid, char *p_buf, size_t p_buf_size) {
  size_t j = 0;

  for (int i = 0; i < 4; i++) {
    int c = ntohl(nrefid) << i * 8 >> 24;
    if (!isalnum(c) || j + 1 >= p_buf_size)
      continue;
    p_buf[j++] = c;
  }
  if (j < p_buf_size)
    p_buf[j] = '\0';
}