static int PTRCALL
notation4(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NOTATION_NONE;
  case XML_TOK_LITERAL:
    state->handler = declClose;
    state->role_none = XML_ROLE_NOTATION_NONE;
    return XML_ROLE_NOTATION_SYSTEM_ID;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return XML_ROLE_NOTATION_NO_SYSTEM_ID;
  }
  return common(state, tok);
}