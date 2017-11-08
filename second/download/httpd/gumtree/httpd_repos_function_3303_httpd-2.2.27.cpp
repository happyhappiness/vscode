static int PTRCALL
entity10(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ENTITY_NONE;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return XML_ROLE_ENTITY_COMPLETE;
  }
  return common(state, tok);
}