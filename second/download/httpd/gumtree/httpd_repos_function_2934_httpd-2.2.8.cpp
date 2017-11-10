static
int attlist2(PROLOG_STATE *state,
	     int tok,
	     const char *ptr,
	     const char *end,
	     const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_NAME:
    {
      static const char *types[] = {
	KW_CDATA,
        KW_ID,
        KW_IDREF,
        KW_IDREFS,
        KW_ENTITY,
        KW_ENTITIES,
        KW_NMTOKEN,
        KW_NMTOKENS,
      };
      int i;
      for (i = 0; i < (int)(sizeof(types)/sizeof(types[0])); i++)
	if (XmlNameMatchesAscii(enc, ptr, end, types[i])) {
	  state->handler = attlist8;
	  return XML_ROLE_ATTRIBUTE_TYPE_CDATA + i;
	}
    }
    if (XmlNameMatchesAscii(enc, ptr, end, KW_NOTATION)) {
      state->handler = attlist5;
      return XML_ROLE_NONE;
    }
    break;
  case XML_TOK_OPEN_PAREN:
    state->handler = attlist3;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}