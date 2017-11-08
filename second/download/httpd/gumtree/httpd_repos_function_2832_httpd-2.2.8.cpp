static
const XML_Char *getContext(XML_Parser parser)
{
  HASH_TABLE_ITER iter;
  int needSep = 0;

  if (dtd.defaultPrefix.binding) {
    int i;
    int len;
    if (!poolAppendChar(&tempPool, XML_T('=')))
      return 0;
    len = dtd.defaultPrefix.binding->uriLen;
    if (namespaceSeparator != XML_T('\0'))
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, dtd.defaultPrefix.binding->uri[i]))
  	return 0;
    needSep = 1;
  }

  hashTableIterInit(&iter, &(dtd.prefixes));
  for (;;) {
    int i;
    int len;
    const XML_Char *s;
    PREFIX *prefix = (PREFIX *)hashTableIterNext(&iter);
    if (!prefix)
      break;
    if (!prefix->binding)
      continue;
    if (needSep && !poolAppendChar(&tempPool, CONTEXT_SEP))
      return 0;
    for (s = prefix->name; *s; s++)
      if (!poolAppendChar(&tempPool, *s))
        return 0;
    if (!poolAppendChar(&tempPool, XML_T('=')))
      return 0;
    len = prefix->binding->uriLen;
    if (namespaceSeparator != XML_T('\0'))
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, prefix->binding->uri[i]))
        return 0;
    needSep = 1;
  }


  hashTableIterInit(&iter, &(dtd.generalEntities));
  for (;;) {
    const XML_Char *s;
    ENTITY *e = (ENTITY *)hashTableIterNext(&iter);
    if (!e)
      break;
    if (!e->open)
      continue;
    if (needSep && !poolAppendChar(&tempPool, CONTEXT_SEP))
      return 0;
    for (s = e->name; *s; s++)
      if (!poolAppendChar(&tempPool, *s))
        return 0;
    needSep = 1;
  }

  if (!poolAppendChar(&tempPool, XML_T('\0')))
    return 0;
  return tempPool.start;
}