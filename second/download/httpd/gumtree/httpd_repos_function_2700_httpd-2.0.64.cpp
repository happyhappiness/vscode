static int PTRCALL
element1(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ELEMENT_NONE;
  case XML_TOK_NAME:
    if (XmlNameMatchesAscii(enc, ptr, end, KW_EMPTY)) {
      state->handler = declClose;
      state->role_none = XML_ROLE_ELEMENT_NONE;
      return XML_ROLE_CONTENT_EMPTY;
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_ANY)) {
      state->handler = declClose;
      state->role_none = XML_ROLE_ELEMENT_NONE;
      return XML_ROLE_CONTENT_ANY;
    }
    break;
  case XML_TOK_OPEN_PAREN:
    state->handler = element2;
    state->level = 1;
    return XML_ROLE_GROUP_OPEN;
  }
  return common(state, tok);
}