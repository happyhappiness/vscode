static
int attlist4(PROLOG_STATE *state,
	     int tok,
	     const char *ptr,
	     const char *end,
	     const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_CLOSE_PAREN:
    state->handler = attlist8;
    return XML_ROLE_NONE;
  case XML_TOK_OR:
    state->handler = attlist3;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}