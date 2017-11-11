static enum XML_Error PTRCALL
entityValueInitProcessor(XML_Parser parser,
                         const char *s,
                         const char *end,
                         const char **nextPtr)
{
  const char *start = s;
  const char *next = s;
  int tok;

  for (;;) {
    tok = XmlPrologTok(encoding, start, end, &next);
    if (tok <= 0) {
      if (nextPtr != 0 && tok != XML_TOK_INVALID) {
              *nextPtr = s;
              return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
              return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
              return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
              return XML_ERROR_PARTIAL_CHAR;
      case XML_TOK_NONE:   /* start == end */
      default:
        break;
      }
      return storeEntityValue(parser, encoding, s, end);
    }
    else if (tok == XML_TOK_XML_DECL) {
      enum XML_Error result = processXmlDecl(parser, 0, start, next);
            if (result != XML_ERROR_NONE)
              return result;
      if (nextPtr) *nextPtr = next;
      /* stop scanning for text declaration - we found one */
      processor = entityValueProcessor;
      return entityValueProcessor(parser, next, end, nextPtr);
    }
    /* If we are at the end of the buffer, this would cause XmlPrologTok to
       return XML_TOK_NONE on the next call, which would then cause the
       function to exit with *nextPtr set to s - that is what we want for other
       tokens, but not for the BOM - we would rather like to skip it;
       then, when this routine is entered the next time, XmlPrologTok will
       return XML_TOK_INVALID, since the BOM is still in the buffer
    */
    else if (tok == XML_TOK_BOM && next == end && nextPtr) {
      *nextPtr = next;
      return XML_ERROR_NONE;
    }
    start = next;
  }
}