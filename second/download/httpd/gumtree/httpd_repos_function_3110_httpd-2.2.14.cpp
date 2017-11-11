static int copyEntityTable(HASH_TABLE *newTable,
			   STRING_POOL *newPool,
			   const HASH_TABLE *oldTable,
			   XML_Parser parser)
{
  HASH_TABLE_ITER iter;
  const XML_Char *cachedOldBase = 0;
  const XML_Char *cachedNewBase = 0;

  hashTableIterInit(&iter, oldTable);

  for (;;) {
    ENTITY *newE;
    const XML_Char *name;
    const ENTITY *oldE = (ENTITY *)hashTableIterNext(&iter);
    if (!oldE)
      break;
    name = poolCopyString(newPool, oldE->name);
    if (!name)
      return 0;
    newE = (ENTITY *)lookup(newTable, name, sizeof(ENTITY));
    if (!newE)
      return 0;
    if (oldE->systemId) {
      const XML_Char *tem = poolCopyString(newPool, oldE->systemId);
      if (!tem)
	return 0;
      newE->systemId = tem;
      if (oldE->base) {
	if (oldE->base == cachedOldBase)
	  newE->base = cachedNewBase;
	else {
	  cachedOldBase = oldE->base;
	  tem = poolCopyString(newPool, cachedOldBase);
	  if (!tem)
	    return 0;
	  cachedNewBase = newE->base = tem;
	}
      }
    }
    else {
      const XML_Char *tem = poolCopyStringN(newPool, oldE->textPtr, oldE->textLen);
      if (!tem)
	return 0;
      newE->textPtr = tem;
      newE->textLen = oldE->textLen;
    }
    if (oldE->notation) {
      const XML_Char *tem = poolCopyString(newPool, oldE->notation);
      if (!tem)
	return 0;
      newE->notation = tem;
    }
  }
  return 1;
}