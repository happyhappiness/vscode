static enum XML_Error
doContent(XML_Parser parser,
	  int startTagLevel,
	  const ENCODING *enc,
	  const char *s,
	  const char *end,
	  const char **nextPtr)
{
  const char **eventPP;
  const char **eventEndPP;
  if (enc == encoding) {
    eventPP = &eventPtr;
    eventEndPP = &eventEndPtr;
  }
  else {
    eventPP = &(openInternalEntities->internalEventPtr);
    eventEndPP = &(openInternalEntities->internalEventEndPtr);
  }
  *eventPP = s;
  for (;;) {
    const char *next = s; /* XmlContentTok doesn't always set the last arg */
    int tok = XmlContentTok(enc, s, end, &next);
    *eventEndPP = next;
    switch (tok) {
    case XML_TOK_TRAILING_CR:
      if (nextPtr) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      *eventEndPP = end;
      if (characterDataHandler) {
	XML_Char c = 0xA;
	characterDataHandler(handlerArg, &c, 1);
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, end);
      if (startTagLevel == 0)
	return XML_ERROR_NO_ELEMENTS;
      if (tagLevel != startTagLevel)
	return XML_ERROR_ASYNC_ENTITY;
      return XML_ERROR_NONE;
    case XML_TOK_NONE:
      if (nextPtr) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      if (startTagLevel > 0) {
	if (tagLevel != startTagLevel)
	  return XML_ERROR_ASYNC_ENTITY;
	return XML_ERROR_NONE;
      }
      return XML_ERROR_NO_ELEMENTS;
    case XML_TOK_INVALID:
      *eventPP = next;
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
    case XML_TOK_ENTITY_REF:
      {
	const XML_Char *name;
	ENTITY *entity;
	XML_Char ch = XmlPredefinedEntityName(enc,
					      s + enc->minBytesPerChar,
					      next - enc->minBytesPerChar);
	if (ch) {
	  if (characterDataHandler)
	    characterDataHandler(handlerArg, &ch, 1);
	  else if (defaultHandler)
	    reportDefault(parser, enc, s, next);
	  break;
	}
	name = poolStoreString(&dtd.pool, enc,
				s + enc->minBytesPerChar,
				next - enc->minBytesPerChar);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	entity = (ENTITY *)lookup(&dtd.generalEntities, name, 0);
	poolDiscard(&dtd.pool);
	if (!entity) {
	  if (dtd.complete || dtd.standalone)
	    return XML_ERROR_UNDEFINED_ENTITY;
	  if (defaultHandler)
	    reportDefault(parser, enc, s, next);
	  break;
	}
	if (entity->open)
	  return XML_ERROR_RECURSIVE_ENTITY_REF;
	if (entity->notation)
	  return XML_ERROR_BINARY_ENTITY_REF;
	if (entity) {
	  if (entity->textPtr) {
	    enum XML_Error result;
	    OPEN_INTERNAL_ENTITY openEntity;
	    if (defaultHandler && !defaultExpandInternalEntities) {
	      reportDefault(parser, enc, s, next);
	      break;
	    }
	    entity->open = 1;
	    openEntity.next = openInternalEntities;
	    openInternalEntities = &openEntity;
	    openEntity.entity = entity;
	    openEntity.internalEventPtr = 0;
	    openEntity.internalEventEndPtr = 0;
	    result = doContent(parser,
			       tagLevel,
			       internalEncoding,
			       (char *)entity->textPtr,
			       (char *)(entity->textPtr + entity->textLen),
			       0);
	    entity->open = 0;
	    openInternalEntities = openEntity.next;
	    if (result)
	      return result;
	  }
	  else if (externalEntityRefHandler) {
	    const XML_Char *context;
	    entity->open = 1;
	    context = getContext(parser);
	    entity->open = 0;
	    if (!context)
	      return XML_ERROR_NO_MEMORY;
	    if (!externalEntityRefHandler(externalEntityRefHandlerArg,
				          context,
					  entity->base,
					  entity->systemId,
					  entity->publicId))
	      return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
	    poolDiscard(&tempPool);
	  }
	  else if (defaultHandler)
	    reportDefault(parser, enc, s, next);
	}
	break;
      }
    case XML_TOK_START_TAG_WITH_ATTS:
      if (!startElementHandler) {
	enum XML_Error result = storeAtts(parser, enc, s, 0, 0);
	if (result)
	  return result;
      }
      /* fall through */
    case XML_TOK_START_TAG_NO_ATTS:
      {
	TAG *tag;
	if (freeTagList) {
	  tag = freeTagList;
	  freeTagList = freeTagList->parent;
	}
	else {
	  tag = MALLOC(sizeof(TAG));
	  if (!tag)
	    return XML_ERROR_NO_MEMORY;
	  tag->buf = MALLOC(INIT_TAG_BUF_SIZE);
	  if (!tag->buf)
	    return XML_ERROR_NO_MEMORY;
	  tag->bufEnd = tag->buf + INIT_TAG_BUF_SIZE;
	}
	tag->bindings = 0;
	tag->parent = tagStack;
	tagStack = tag;
	tag->name.localPart = 0;
	tag->rawName = s + enc->minBytesPerChar;
	tag->rawNameLength = XmlNameLength(enc, tag->rawName);
	if (nextPtr) {
	  /* Need to guarantee that:
	     tag->buf + ROUND_UP(tag->rawNameLength, sizeof(XML_Char)) <= tag->bufEnd - sizeof(XML_Char) */
	  if (tag->rawNameLength + (int)(sizeof(XML_Char) - 1) + (int)sizeof(XML_Char) > tag->bufEnd - tag->buf) {
	    int bufSize = tag->rawNameLength * 4;
	    bufSize = ROUND_UP(bufSize, sizeof(XML_Char));
	    tag->buf = REALLOC(tag->buf, bufSize);
	    if (!tag->buf)
	      return XML_ERROR_NO_MEMORY;
	    tag->bufEnd = tag->buf + bufSize;
	  }
	  memcpy(tag->buf, tag->rawName, tag->rawNameLength);
	  tag->rawName = tag->buf;
	}
	++tagLevel;
	if (startElementHandler) {
	  enum XML_Error result;
	  XML_Char *toPtr;
	  for (;;) {
	    const char *rawNameEnd = tag->rawName + tag->rawNameLength;
	    const char *fromPtr = tag->rawName;
	    int bufSize;
	    if (nextPtr)
	      toPtr = (XML_Char *)(tag->buf + ROUND_UP(tag->rawNameLength, sizeof(XML_Char)));
	    else
	      toPtr = (XML_Char *)tag->buf;
	    tag->name.str = toPtr;
	    XmlConvert(enc,
		       &fromPtr, rawNameEnd,
		       (ICHAR **)&toPtr, (ICHAR *)tag->bufEnd - 1);
	    if (fromPtr == rawNameEnd)
	      break;
	    bufSize = (tag->bufEnd - tag->buf) << 1;
	    tag->buf = REALLOC(tag->buf, bufSize);
	    if (!tag->buf)
	      return XML_ERROR_NO_MEMORY;
	    tag->bufEnd = tag->buf + bufSize;
	    if (nextPtr)
	      tag->rawName = tag->buf;
	  }
	  *toPtr = XML_T('\0');
	  result = storeAtts(parser, enc, s, &(tag->name), &(tag->bindings));
	  if (result)
	    return result;
	  startElementHandler(handlerArg, tag->name.str, (const XML_Char **)atts);
	  poolClear(&tempPool);
	}
	else {
	  tag->name.str = 0;
	  if (defaultHandler)
	    reportDefault(parser, enc, s, next);
	}
	break;
      }
    case XML_TOK_EMPTY_ELEMENT_WITH_ATTS:
      if (!startElementHandler) {
	enum XML_Error result = storeAtts(parser, enc, s, 0, 0);
	if (result)
	  return result;
      }
      /* fall through */
    case XML_TOK_EMPTY_ELEMENT_NO_ATTS:
      if (startElementHandler || endElementHandler) {
	const char *rawName = s + enc->minBytesPerChar;
	enum XML_Error result;
	BINDING *bindings = 0;
	TAG_NAME name;
	name.str = poolStoreString(&tempPool, enc, rawName,
				   rawName + XmlNameLength(enc, rawName));
	if (!name.str)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&tempPool);
	result = storeAtts(parser, enc, s, &name, &bindings);
	if (result)
	  return result;
	poolFinish(&tempPool);
	if (startElementHandler)
	  startElementHandler(handlerArg, name.str, (const XML_Char **)atts);
	if (endElementHandler) {
	  if (startElementHandler)
	    *eventPP = *eventEndPP;
	  endElementHandler(handlerArg, name.str);
	}
	poolClear(&tempPool);
	while (bindings) {
	  BINDING *b = bindings;
	  if (endNamespaceDeclHandler)
	    endNamespaceDeclHandler(handlerArg, b->prefix->name);
	  bindings = bindings->nextTagBinding;
	  b->nextTagBinding = freeBindingList;
	  freeBindingList = b;
	  b->prefix->binding = b->prevPrefixBinding;
	}
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, next);
      if (tagLevel == 0)
	return epilogProcessor(parser, next, end, nextPtr);
      break;
    case XML_TOK_END_TAG:
      if (tagLevel == startTagLevel)
        return XML_ERROR_ASYNC_ENTITY;
      else {
	int len;
	const char *rawName;
	TAG *tag = tagStack;
	tagStack = tag->parent;
	tag->parent = freeTagList;
	freeTagList = tag;
	rawName = s + enc->minBytesPerChar*2;
	len = XmlNameLength(enc, rawName);
	if (len != tag->rawNameLength
	    || memcmp(tag->rawName, rawName, len) != 0) {
	  *eventPP = rawName;
	  return XML_ERROR_TAG_MISMATCH;
	}
	--tagLevel;
	if (endElementHandler && tag->name.str) {
	  if (tag->name.localPart) {
	    XML_Char *to = (XML_Char *)tag->name.str + tag->name.uriLen;
	    const XML_Char *from = tag->name.localPart;
	    while ((*to++ = *from++) != 0)
	      ;
	  }
	  endElementHandler(handlerArg, tag->name.str);
	}
	else if (defaultHandler)
	  reportDefault(parser, enc, s, next);
	while (tag->bindings) {
	  BINDING *b = tag->bindings;
	  if (endNamespaceDeclHandler)
	    endNamespaceDeclHandler(handlerArg, b->prefix->name);
	  tag->bindings = tag->bindings->nextTagBinding;
	  b->nextTagBinding = freeBindingList;
	  freeBindingList = b;
	  b->prefix->binding = b->prevPrefixBinding;
	}
	if (tagLevel == 0)
	  return epilogProcessor(parser, next, end, nextPtr);
      }
      break;
    case XML_TOK_CHAR_REF:
      {
	int n = XmlCharRefNumber(enc, s);
	if (n < 0)
	  return XML_ERROR_BAD_CHAR_REF;
	if (characterDataHandler) {
	  XML_Char buf[XML_ENCODE_MAX];
	  characterDataHandler(handlerArg, buf, XmlEncode(n, (ICHAR *)buf));
	}
	else if (defaultHandler)
	  reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_XML_DECL:
      return XML_ERROR_MISPLACED_XML_PI;
    case XML_TOK_DATA_NEWLINE:
      if (characterDataHandler) {
	XML_Char c = 0xA;
	characterDataHandler(handlerArg, &c, 1);
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_CDATA_SECT_OPEN:
      {
	enum XML_Error result;
	if (startCdataSectionHandler)
  	  startCdataSectionHandler(handlerArg);
#if 0
	/* Suppose you doing a transformation on a document that involves
	   changing only the character data.  You set up a defaultHandler
	   and a characterDataHandler.  The defaultHandler simply copies
	   characters through.  The characterDataHandler does the transformation
	   and writes the characters out escaping them as necessary.  This case
	   will fail to work if we leave out the following two lines (because &
	   and < inside CDATA sections will be incorrectly escaped).

	   However, now we have a start/endCdataSectionHandler, so it seems
	   easier to let the user deal with this. */

	else if (characterDataHandler)
  	  characterDataHandler(handlerArg, dataBuf, 0);
#endif
	else if (defaultHandler)
	  reportDefault(parser, enc, s, next);
	result = doCdataSection(parser, enc, &next, end, nextPtr);
	if (!next) {
	  processor = cdataSectionProcessor;
	  return result;
	}
      }
      break;
    case XML_TOK_TRAILING_RSQB:
      if (nextPtr) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      if (characterDataHandler) {
	if (MUST_CONVERT(enc, s)) {
	  ICHAR *dataPtr = (ICHAR *)dataBuf;
	  XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)dataBufEnd);
	  characterDataHandler(handlerArg, dataBuf, dataPtr - (ICHAR *)dataBuf);
	}
	else
	  characterDataHandler(handlerArg,
		  	       (XML_Char *)s,
			       (XML_Char *)end - (XML_Char *)s);
      }
      else if (defaultHandler)
	reportDefault(parser, enc, s, end);
      if (startTagLevel == 0) {
        *eventPP = end;
	return XML_ERROR_NO_ELEMENTS;
      }
      if (tagLevel != startTagLevel) {
	*eventPP = end;
	return XML_ERROR_ASYNC_ENTITY;
      }
      return XML_ERROR_NONE;
    case XML_TOK_DATA_CHARS:
      if (characterDataHandler) {
	if (MUST_CONVERT(enc, s)) {
	  for (;;) {
	    ICHAR *dataPtr = (ICHAR *)dataBuf;
	    XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)dataBufEnd);
	    *eventEndPP = s;
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
    case XML_TOK_PI:
      if (!reportProcessingInstruction(parser, enc, s, next))
	return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_COMMENT:
      if (!reportComment(parser, enc, s, next))
	return XML_ERROR_NO_MEMORY;
      break;
    default:
      if (defaultHandler)
	reportDefault(parser, enc, s, next);
      break;
    }
    *eventPP = s = next;
  }
  /* not reached */
}