static enum XML_Error PTRCALL
epilogProcessor(XML_Parser parser,
                const char *s,
                const char *end,
                const char **nextPtr)
{
  processor = epilogProcessor;
  eventPtr = s;
  for (;;) {
    const char *next = NULL;
    int tok = XmlPrologTok(encoding, s, end, &next);
    eventEndPtr = next;
    switch (tok) {
    /* report partial linebreak - it might be the last token */
    case -XML_TOK_PROLOG_S:
      if (defaultHandler) {
        eventEndPtr = next;
        reportDefault(parser, encoding, s, next);
      }
      if (nextPtr)
        *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_TOK_NONE:
      if (nextPtr)
        *nextPtr = s;
      return XML_ERROR_NONE;
    case XML_TOK_PROLOG_S:
      if (defaultHandler)
        reportDefault(parser, encoding, s, next);
      break;
    case XML_TOK_PI:
      if (!reportProcessingInstruction(parser, encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_COMMENT:
      if (!reportComment(parser, encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_INVALID:
      eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (nextPtr) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (nextPtr) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    default:
      return XML_ERROR_JUNK_AFTER_DOC_ELEMENT;
    }
    eventPtr = s = next;
  }
}