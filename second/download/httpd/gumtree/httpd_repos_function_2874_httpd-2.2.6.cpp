static
int entity1(PROLOG_STATE *state,
	    int tok,
	    const char *ptr,
	    const char *end,
	    const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_NAME:
    state->handler = entity7;
    return XML_ROLE_PARAM_ENTITY_NAME;
  }
  return common(state, tok);
}