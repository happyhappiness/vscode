static int PTRCALL
declClose(PROLOG_STATE *state,
          int tok,
          const char *ptr,
          const char *end,
          const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return state->role_none;
  case XML_TOK_DECL_CLOSE:
    setTopLevel(state);
    return state->role_none;
  }
  return common(state, tok);
}