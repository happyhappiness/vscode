static int dtdInit(DTD *p, XML_Parser parser)
{
  XML_Memory_Handling_Suite *ms = &((Parser *) parser)->m_mem; 
  poolInit(&(p->pool), ms);
  hashTableInit(&(p->generalEntities), ms);
  hashTableInit(&(p->elementTypes), ms);
  hashTableInit(&(p->attributeIds), ms);
  hashTableInit(&(p->prefixes), ms);
  p->complete = 1;
  p->standalone = 0;
#ifdef XML_DTD
  hashTableInit(&(p->paramEntities), ms);
#endif /* XML_DTD */
  p->defaultPrefix.name = 0;
  p->defaultPrefix.binding = 0;

  p->in_eldecl = 0;
  p->scaffIndex = 0;
  p->scaffLevel = 0;
  p->scaffold = 0;
  p->contentStringLen = 0;
  p->scaffSize = 0;
  p->scaffCount = 0;

  return 1;
}