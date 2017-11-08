static
int entity7(PROLOG_STATE *state,
	    int tok,
	    const char *ptr,
	    const char *end,
	    const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_NAME:
    if (XmlNameMatchesAscii(enc, ptr, end, KW_SYSTEM)) {
      state->handler = entity9;
      return XML_ROLE_NONE;
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_PUBLIC)) {
      state->handler = entity8;
      return XML_ROLE_NONE;
    }
    break;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    return XML_ROLE_ENTITY_VALUE;
  }
  return common(state, tok);
}