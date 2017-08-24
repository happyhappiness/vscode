{
    int i;
    int len;
    const XML_Char *s;
    PREFIX *prefix = (PREFIX *)hashTableIterNext(&iter);
    if (!prefix)
      break;
    if (!prefix->binding)
      continue;
    if (needSep && !poolAppendChar(&tempPool, CONTEXT_SEP))
      return NULL;
    for (s = prefix->name; *s; s++)
      if (!poolAppendChar(&tempPool, *s))
        return NULL;
    if (!poolAppendChar(&tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = prefix->binding->uriLen;
    if (namespaceSeparator)
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, prefix->binding->uri[i]))
        return NULL;
    needSep = XML_TRUE;
  }