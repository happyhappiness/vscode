static
int element5(PROLOG_STATE *state,
	     int tok,
	     const char *ptr,
	     const char *end,
	     const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_CLOSE_PAREN_ASTERISK:
    state->handler = declClose;
    return XML_ROLE_GROUP_CLOSE_REP;
  case XML_TOK_OR:
    state->handler = element4;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}