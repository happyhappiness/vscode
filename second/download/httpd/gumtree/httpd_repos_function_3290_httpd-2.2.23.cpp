static int PTRCALL
notation0(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NOTATION_NONE;
  case XML_TOK_NAME:
    state->handler = notation1;
    return XML_ROLE_NOTATION_NAME;
  }
  return common(state, tok);
}