static enum XML_Error
appendAttributeValue(XML_Parser parser, const ENCODING *enc, int isCdata,
		     const char *ptr, const char *end,
		     STRING_POOL *pool)
{
  for (;;) {
    const char *next;
    int tok = XmlAttributeValueTok(enc, ptr, end, &next);
    switch (tok) {
    case XML_TOK_NONE:
      return XML_ERROR_NONE;
    case XML_TOK_INVALID:
      if (enc == encoding)
	eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (enc == encoding)
	eventPtr = ptr;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_CHAR_REF:
      {
	XML_Char buf[XML_ENCODE_MAX];
	int i;
	int n = XmlCharRefNumber(enc, ptr);
	if (n < 0) {
	  if (enc == encoding)
	    eventPtr = ptr;
      	  return XML_ERROR_BAD_CHAR_REF;
	}
	if (!isCdata
	    && n == 0x20 /* space */
	    && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
	  break;
	n = XmlEncode(n, (ICHAR *)buf);
	if (!n) {
	  if (enc == encoding)
	    eventPtr = ptr;
	  return XML_ERROR_BAD_CHAR_REF;
	}
	for (i = 0; i < n; i++) {
	  if (!poolAppendChar(pool, buf[i]))
	    return XML_ERROR_NO_MEMORY;
	}
      }
      break;
    case XML_TOK_DATA_CHARS:
      if (!poolAppend(pool, enc, ptr, next))
	return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_TRAILING_CR:
      next = ptr + enc->minBytesPerChar;
      /* fall through */
    case XML_TOK_ATTRIBUTE_VALUE_S:
    case XML_TOK_DATA_NEWLINE:
      if (!isCdata && (poolLength(pool) == 0 || poolLastChar(pool) == 0x20))
	break;
      if (!poolAppendChar(pool, 0x20))
	return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_ENTITY_REF:
      {
	const XML_Char *name;
	ENTITY *entity;
	XML_Char ch = XmlPredefinedEntityName(enc,
					      ptr + enc->minBytesPerChar,
					      next - enc->minBytesPerChar);
	if (ch) {
	  if (!poolAppendChar(pool, ch))
  	    return XML_ERROR_NO_MEMORY;
	  break;
	}
	name = poolStoreString(&temp2Pool, enc,
			       ptr + enc->minBytesPerChar,
			       next - enc->minBytesPerChar);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	entity = (ENTITY *)lookup(&dtd.generalEntities, name, 0);
	poolDiscard(&temp2Pool);
	if (!entity) {
	  if (dtd.complete) {
	    if (enc == encoding)
	      eventPtr = ptr;
	    return XML_ERROR_UNDEFINED_ENTITY;
	  }
	}
	else if (entity->open) {
	  if (enc == encoding)
	    eventPtr = ptr;
	  return XML_ERROR_RECURSIVE_ENTITY_REF;
	}
	else if (entity->notation) {
	  if (enc == encoding)
	    eventPtr = ptr;
	  return XML_ERROR_BINARY_ENTITY_REF;
	}
	else if (!entity->textPtr) {
	  if (enc == encoding)
	    eventPtr = ptr;
  	  return XML_ERROR_ATTRIBUTE_EXTERNAL_ENTITY_REF;
	}
	else {
	  enum XML_Error result;
	  const XML_Char *textEnd = entity->textPtr + entity->textLen;
	  entity->open = 1;
	  result = appendAttributeValue(parser, internalEncoding, isCdata, (char *)entity->textPtr, (char *)textEnd, pool);
	  entity->open = 0;
	  if (result)
	    return result;
	}
      }
      break;
    default:
      if (enc == encoding)
	eventPtr = ptr;
      return XML_ERROR_UNEXPECTED_STATE;
    }
    ptr = next;
  }
  /* not reached */
}