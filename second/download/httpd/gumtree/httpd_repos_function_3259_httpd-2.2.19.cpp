static int PTRCALL
attlist8(PROLOG_STATE *state,
         int tok,
         const char *ptr,
         const char *end,
         const ENCODING *enc)
{
  switch (tok) {
  case XML_TOK_PROLOG_S:
    return XML_ROLE_ATTLIST_NONE;
  case XML_TOK_POUND_NAME:
    if (XmlNameMatchesAscii(enc,
                            ptr + MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_IMPLIED)) {
      state->handler = attlist1;
      return XML_ROLE_IMPLIED_ATTRIBUTE_VALUE;
    }
    if (XmlNameMatchesAscii(enc,
                            ptr + MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_REQUIRED)) {
      state->handler = attlist1;
      return XML_ROLE_REQUIRED_ATTRIBUTE_VALUE;
    }
    if (XmlNameMatchesAscii(enc,
                            ptr + MIN_BYTES_PER_CHAR(enc),
                            end,
                            KW_FIXED)) {
      state->handler = attlist9;
      return XML_ROLE_ATTLIST_NONE;
    }
    break;
  case XML_TOK_LITERAL:
    state->handler = attlist1;
    return XML_ROLE_DEFAULT_ATTRIBUTE_VALUE;
  }
  return common(state, tok);
}