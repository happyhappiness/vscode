static int PTRCALL
entity6(PROLOG_STATE *state,
        int tok,
        const char *ptr,
        const char *end,
        const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ENTITY_NONE;
  case XML_TOK_NAME:
    state->handler = declClose;
    state->role_none = XML_ROLE_ENTITY_NONE;
    return XML_ROLE_ENTITY_NOTATION_NAME;
  }
  return common(state, tok);
}