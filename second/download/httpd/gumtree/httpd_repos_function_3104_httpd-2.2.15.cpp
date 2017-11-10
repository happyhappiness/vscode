static
enum XML_Error doCdataSection(XML_Parser parser,
			      const ENCODING *enc,
			      const char **startPtr,
			      const char *end,
			      const char **nextPtr)
{
  const char *s = *startPtr;
  const char **eventPP;
  const char **eventEndPP;
  if (enc == encoding) {
    eventPP = &eventPtr;
    *eventPP = s;
    eventEndPP = &eventEndPtr;
  }
  else {
    eventPP = &(openInternalEntities->internalEventPtr);
    eventEndPP = &(openInternalEntities->internalEventEndPtr);
  }
  *eventPP = s;
  *startPtr = 0;
  for (;;) {
    const char *next;
    int tok = XmlCdataSectionTok(enc, s, end, &next);
    *eventEndPP = next;
    switch (tok) {
    case XML_TOK_CDATA_SECT_CLOSE:
      if (endCdataSectionHandler)
	endCdataSectionHandler(handlerArg);
#if 0
      /* see comment under XML_TOK_CDATA_SECT_OPEN */
      else if (characterDataHandler)
	characterDataHandler(handlerArg, dataBuf, 0);
#endif
      else if (defaultHandler)
	reportDefault(parser, enc, s, next);
      *startPtr = next;
      return XML_ERROR_NONE;
    case XML_TOK_DATA_NEWLINE:
      if (characterDataHandler) {
	XML_Char c = 0xA;
	characterDataHandler(handlerArg, &c, 1);
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_DATA_CHARS:
      if (characterDataHandler) {
	if (MUST_CONVERT(enc, s)) {
	  for (;;) {
  	    ICHAR *dataPtr = (ICHAR *)dataBuf;
	    XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)dataBufEnd);
	    *eventEndPP = next;
	    characterDataHandler(handlerArg, dataBuf, dataPtr - (ICHAR *)dataBuf);
	    if (s == next)
	      break;
	    *eventPP = s;
	  }
	}
	else
	  characterDataHandler(handlerArg,
		  	       (XML_Char *)s,
			       (XML_Char *)next - (XML_Char *)s);
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_INVALID:
      *eventPP = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (nextPtr) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_PARTIAL:
    case XML_TOK_NONE:
      if (nextPtr) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_CDATA_SECTION;
    default:
      *eventPP = next;
      return XML_ERROR_UNEXPECTED_STATE;
    }
    *eventPP = s = next;
  }
  /* not reached */
}