static int PTRCALL
attlist1(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ATTLIST_NONE;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return XML_ROLE_ATTLIST_NONE;
  case XML_TOK_NAME:
  case XML_TOK_PREFIXED_NAME:
    state->handler = attlist2;
    return XML_ROLE_ATTRIBUTE_NAME;
  }
  return common(state, tok);
}