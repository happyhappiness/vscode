static
int entity9(PROLOG_STATE *state,
	    int tok,
	    const char *ptr,
	    const char *end,
	    const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    return XML_ROLE_ENTITY_SYSTEM_ID;
  }
  return common(state, tok);
}