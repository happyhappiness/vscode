static int PTRCALL
doctype4(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_DOCTYPE_NONE;
  case XML_TOK_OPEN_BRACKET:
    state->handler = internalSubset;
    return XML_ROLE_DOCTYPE_INTERNAL_SUBSET;
  case XML_TOK_DECL_CLOSE:
    state->handler = prolog2;
    return XML_ROLE_DOCTYPE_CLOSE;
  }
  return common(state, tok);
}