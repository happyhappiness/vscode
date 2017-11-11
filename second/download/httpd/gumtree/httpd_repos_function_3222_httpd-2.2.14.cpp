static
int condSect1(PROLOG_STATE *state,
	      int tok,
	      const char *ptr,
	      const char *end,
	      const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_OPEN_BRACKET:
    state->handler = externalSubset1;
    state->includeLevel += 1;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}