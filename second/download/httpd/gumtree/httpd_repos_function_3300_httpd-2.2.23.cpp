static int PTRCALL
attlist5(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ATTLIST_NONE;
  case XML_TOK_OPEN_PAREN:
    state->handler = attlist6;
    return XML_ROLE_ATTLIST_NONE;
  }
  return common(state, tok);
}