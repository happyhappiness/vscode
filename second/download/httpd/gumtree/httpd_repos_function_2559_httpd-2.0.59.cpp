static
int setContext(XML_Parser parser, const XML_Char *context)
{
  const XML_Char *s = context;

  while (*context != XML_T('\0')) {
    if (*s == CONTEXT_SEP || *s == XML_T('\0')) {
      ENTITY *e;
      if (!poolAppendChar(&tempPool, XML_T('\0')))
	return 0;
      e = (ENTITY *)lookup(&dtd.generalEntities, poolStart(&tempPool), 0);
      if (e)
	e->open = 1;
      if (*s != XML_T('\0'))
	s++;
      context = s;
      poolDiscard(&tempPool);
    }
    else if (*s == '=') {
      PREFIX *prefix;
      if (poolLength(&tempPool) == 0)
	prefix = &dtd.defaultPrefix;
      else {
	if (!poolAppendChar(&tempPool, XML_T('\0')))
	  return 0;
	prefix = (PREFIX *)lookup(&dtd.prefixes, poolStart(&tempPool), sizeof(PREFIX));
	if (!prefix)
	  return 0;
        if (prefix->name == poolStart(&tempPool)) {
	  prefix->name = poolCopyString(&dtd.pool, prefix->name);
	  if (!prefix->name)
	    return 0;
	}
	poolDiscard(&tempPool);
      }
      for (context = s + 1; *context != CONTEXT_SEP && *context != XML_T('\0'); context++)
        if (!poolAppendChar(&tempPool, *context))
          return 0;
      if (!poolAppendChar(&tempPool, XML_T('\0')))
	return 0;
      if (!addBinding(parser, prefix, 0, poolStart(&tempPool), &inheritedBindings))
	return 0;
      poolDiscard(&tempPool);
      if (*context != XML_T('\0'))
	++context;
      s = context;
    }
    else {
      if (!poolAppendChar(&tempPool, *s))
	return 0;
      s++;
    }
  }
  return 1;
}