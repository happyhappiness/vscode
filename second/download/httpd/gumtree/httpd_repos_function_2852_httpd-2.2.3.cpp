static
int internalSubset(PROLOG_STATE *state,
		   int tok,
		   const char *ptr,
		   const char *end,
		   const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_NONE;
  case XML_TOK_DECL_OPEN:
    if (XmlNameMatchesAscii(enc,
			    ptr + 2 * MIN_BYTES_PER_CHAR(enc),
			    end,
			    KW_ENTITY)) {
      state->handler = entity0;
      return XML_ROLE_NONE;
    }
    if (XmlNameMatchesAscii(enc,
			    ptr + 2 * MIN_BYTES_PER_CHAR(enc),
			    end,
			    KW_ATTLIST)) {
      state->handler = attlist0;
      return XML_ROLE_NONE;
    }
    if (XmlNameMatchesAscii(enc,
			    ptr + 2 * MIN_BYTES_PER_CHAR(enc),
			    end,
			    KW_ELEMENT)) {
      state->handler = element0;
      return XML_ROLE_NONE;
    }
    if (XmlNameMatchesAscii(enc,
			    ptr + 2 * MIN_BYTES_PER_CHAR(enc),
			    end,
			    KW_NOTATION)) {
      state->handler = notation0;
      return XML_ROLE_NONE;
    }
    break;
  case XML_TOK_PI:
  case XML_TOK_COMMENT:
    return XML_ROLE_NONE;
  case XML_TOK_PARAM_ENTITY_REF:
    return XML_ROLE_PARAM_ENTITY_REF;
  case XML_TOK_CLOSE_BRACKET:
    state->handler = doctype5;
    return XML_ROLE_NONE;
  }
  return common(state, tok);
}