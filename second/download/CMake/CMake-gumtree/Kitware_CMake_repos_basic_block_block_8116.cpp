{
    int i;
    int len;
    if (!poolAppendChar(&tempPool, XML_T(ASCII_EQUALS)))
      return NULL;
    len = dtd->defaultPrefix.binding->uriLen;
    if (namespaceSeparator)
      len--;
    for (i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, dtd->defaultPrefix.binding->uri[i]))
        return NULL;
    needSep = XML_TRUE;
  }