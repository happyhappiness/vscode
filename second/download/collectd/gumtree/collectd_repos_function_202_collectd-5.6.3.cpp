static void gr_copy_escape_part(char *dst, const char *src, size_t dst_len,
                                char escape_char) {
  memset(dst, 0, dst_len);

  if (src == NULL)
    return;

  for (size_t i = 0; i < dst_len; i++) {
    if (src[i] == 0) {
      dst[i] = 0;
      break;
    }

    if ((src[i] == '.') || isspace((int)src[i]) || iscntrl((int)src[i]))
      dst[i] = escape_char;
    else
      dst[i] = src[i];
  }
}