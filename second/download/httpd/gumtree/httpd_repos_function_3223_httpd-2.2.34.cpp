static enum XML_Error
processInternalParamEntity(XML_Parser parser, ENTITY *entity)
{
  const char *s, *end, *next;
  int tok;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY openEntity;
  entity->open = XML_TRUE;
  openEntity.next = openInternalEntities;
  openInternalEntities = &openEntity;
  openEntity.entity = entity;
  openEntity.internalEventPtr = NULL;
  openEntity.internalEventEndPtr = NULL;
  s = (char *)entity->textPtr;
  end = (char *)(entity->textPtr + entity->textLen);
  tok = XmlPrologTok(internalEncoding, s, end, &next);
  result = doProlog(parser, internalEncoding, s, end, tok, next, 0);
  entity->open = XML_FALSE;
  openInternalEntities = openEntity.next;
  return result;
}