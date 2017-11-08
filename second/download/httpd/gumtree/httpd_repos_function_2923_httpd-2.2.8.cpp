static
int entity6(PROLOG_STATE *state,
	    int tok,
	    const char *ptr,
	    const char *end,
	    const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_NAME:
    state->handler = declClose;
    return XML_ROLE_ENTITY_NOTATION_NAME;
  }
  return common(state, tok);
}