static int PTRCALL
PREFIX(scanComment)(const ENCODING *enc, const char *ptr,
                    const char *end, const char **nextTokPtr)
{
  if (ptr != end) {
    if (!CHAR_MATCHES(enc, ptr, ASCII_MINUS)) {
      *nextTokPtr = ptr;
      return XML_TOK_INVALID;
    }
    ptr += MINBPC(enc);
    while (ptr != end) {
      switch (BYTE_TYPE(enc, ptr)) {
      INVALID_CASES(ptr, nextTokPtr)
      case BT_MINUS:
        if ((ptr += MINBPC(enc)) == end)
          return XML_TOK_PARTIAL;
        if (CHAR_MATCHES(enc, ptr, ASCII_MINUS)) {
          if ((ptr += MINBPC(enc)) == end)
            return XML_TOK_PARTIAL;
          if (!CHAR_MATCHES(enc, ptr, ASCII_GT)) {
            *nextTokPtr = ptr;
            return XML_TOK_INVALID;
          }
          *nextTokPtr = ptr + MINBPC(enc);
          return XML_TOK_COMMENT;
        }
        break;
      default:
        ptr += MINBPC(enc);
        break;
      }
    }
  }
  return XML_TOK_PARTIAL;
}