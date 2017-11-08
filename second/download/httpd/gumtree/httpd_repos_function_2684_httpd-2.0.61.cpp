static
int common(PROLOG_STATE *state, int tok)
{
#ifdef XML_DTD
  if (!state->documentEntity && tok == XML_TOK_PARAM_ENTITY_REF)
    return XML_ROLE_INNER_PARAM_ENTITY_REF;
#endif
  state->handler = error;
  return XML_ROLE_ERROR;
}