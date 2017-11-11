static enum XML_Error
processInternalParamEntity(XML_Parser parser, ENTITY *entity)
{
  const char *s, *end, *next;
  int tok;
  enum XML_Error result;
  OPEN_INTERNAL_ENTITY openEntity;
  entity->open = 1;
  openEntity.next = openInternalEntities;
  openInternalEntities = &openEntity;
  openEntity.entity = entity;
  openEntity.internalEventPtr = 0;
  openEntity.internalEventEndPtr = 0;
  s = (char *)entity->textPtr;
  end = (char *)(entity->textPtr + entity->textLen);
  tok = XmlPrologTok(internalEncoding, s, end, &next);
  result = doProlog(parser, internalEncoding, s, end, tok, next, 0);
  entity->open = 0;
  openInternalEntities = openEntity.next;
  return result;
}