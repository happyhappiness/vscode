static int PTRCALL
notation1(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NOTATION_NONE;
  case XML_TOK_NAME:
    if (XmlNameMatchesAscii(enc, ptr, end, KW_SYSTEM)) {
      state->handler = notation3;
      return XML_ROLE_NOTATION_NONE;
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_PUBLIC)) {
      state->handler = notation2;
      return XML_ROLE_NOTATION_NONE;
    }
    break;
  }
  return common(state, tok);
}