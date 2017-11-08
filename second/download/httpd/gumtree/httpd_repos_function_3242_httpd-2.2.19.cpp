static int PTRCALL
entity7(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ENTITY_NONE;
  case XML_TOK_NAME:
    if (XmlNameMatchesAscii(enc, ptr, end, KW_SYSTEM)) {
      state->handler = entity9;
      return XML_ROLE_ENTITY_NONE;
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_PUBLIC)) {
      state->handler = entity8;
      return XML_ROLE_ENTITY_NONE;
    }
    break;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    state->role_none = XML_ROLE_ENTITY_NONE;
    return XML_ROLE_ENTITY_VALUE;
  }
  return common(state, tok);
}