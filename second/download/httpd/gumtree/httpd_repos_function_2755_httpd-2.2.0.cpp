static
enum XML_Error storeEntityValue(XML_Parser parser,
				const ENCODING *enc,
				const char *entityTextPtr,
				const char *entityTextEnd)
{
  STRING_POOL *pool = &(dtd.pool);
  for (;;) {
    const char *next;
    int tok = XmlEntityValueTok(enc, entityTextPtr, entityTextEnd, &next);
    switch (tok) {
    case XML_TOK_PARAM_ENTITY_REF:
#ifdef XML_DTD
      if (parentParser || enc != encoding) {
	enum XML_Error result;
	const XML_Char *name;
	ENTITY *entity;
	name = poolStoreString(&tempPool, enc,
			       entityTextPtr + enc->minBytesPerChar,
			       next - enc->minBytesPerChar);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	entity = (ENTITY *)lookup(&dtd.paramEntities, name, 0);
	poolDiscard(&tempPool);
	if (!entity) {
	  if (enc == encoding)
	    eventPtr = entityTextPtr;
	  return XML_ERROR_UNDEFINED_ENTITY;
	}
	if (entity->open) {
	  if (enc == encoding)
	    eventPtr = entityTextPtr;
	  return XML_ERROR_RECURSIVE_ENTITY_REF;
	}
	if (entity->systemId) {
	  if (enc == encoding)
	    eventPtr = entityTextPtr;
	  return XML_ERROR_PARAM_ENTITY_REF;
	}
	entity->open = 1;
	result = storeEntityValue(parser,
				  internalEncoding,
				  (char *)entity->textPtr,
				  (char *)(entity->textPtr + entity->textLen));
	entity->open = 0;
	if (result)
	  return result;
	break;
      }
#endif /* XML_DTD */
      eventPtr = entityTextPtr;
      return XML_ERROR_SYNTAX;
    case XML_TOK_NONE:
      return XML_ERROR_NONE;
    case XML_TOK_ENTITY_REF:
    case XML_TOK_DATA_CHARS:
      if (!poolAppend(pool, enc, entityTextPtr, next))
	return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_TRAILING_CR:
      next = entityTextPtr + enc->minBytesPerChar;
      /* fall through */
    case XML_TOK_DATA_NEWLINE:
      if (pool->end == pool->ptr && !poolGrow(pool))
	return XML_ERROR_NO_MEMORY;
      *(pool->ptr)++ = 0xA;
      break;
    case XML_TOK_CHAR_REF:
      {
	XML_Char buf[XML_ENCODE_MAX];
	int i;
	int n = XmlCharRefNumber(enc, entityTextPtr);
	if (n < 0) {
	  if (enc == encoding)
	    eventPtr = entityTextPtr;
	  return XML_ERROR_BAD_CHAR_REF;
	}
	n = XmlEncode(n, (ICHAR *)buf);
	if (!n) {
	  if (enc == encoding)
	    eventPtr = entityTextPtr;
	  return XML_ERROR_BAD_CHAR_REF;
	}
	for (i = 0; i < n; i++) {
	  if (pool->end == pool->ptr && !poolGrow(pool))
	    return XML_ERROR_NO_MEMORY;
	  *(pool->ptr)++ = buf[i];
	}
      }
      break;
    case XML_TOK_PARTIAL:
      if (enc == encoding)
	eventPtr = entityTextPtr;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_INVALID:
      if (enc == encoding)
	eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    default:
      if (enc == encoding)
	eventPtr = entityTextPtr;
      return XML_ERROR_UNEXPECTED_STATE;
    }
    entityTextPtr = next;
  }
  /* not reached */
}