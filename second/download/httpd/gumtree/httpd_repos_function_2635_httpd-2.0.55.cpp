static
int entity0(PROLOG_STATE *state,
	    int tok,
	    const char *ptr,
	    const char *end,
	    const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_PERCENT:
    state->handler = entity1;
    return XML_ROLE_NONE;
  case XML_TOK_NAME:
    state->handler = entity2;
    return XML_ROLE_GENERAL_ENTITY_NAME;
  }
  return common(state, tok);
}