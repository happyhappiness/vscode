static
int externalSubset0(PROLOG_STATE *state,
		    int tok,
		    const char *ptr,
		    const char *end,
		    const ENCODING *enc)
{
  state->handler = externalSubset1;
  if (tok == XML_TOK_XML_DECL)
    return XML_ROLE_TEXT_DECL;
  return externalSubset1(state, tok, ptr, end, enc);
}