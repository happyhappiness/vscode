static enum XML_Error storeAtts(XML_Parser parser, const ENCODING *enc,
				const char *attStr, TAG_NAME *tagNamePtr,
				BINDING **bindingsPtr)
{
  ELEMENT_TYPE *elementType = 0;
  int nDefaultAtts = 0;
  const XML_Char **appAtts;   /* the attribute list to pass to the application */
  int attIndex = 0;
  int i;
  int n;
  int nPrefixes = 0;
  BINDING *binding;
  const XML_Char *localPart;

  /* lookup the element type name */
  if (tagNamePtr) {
    elementType = (ELEMENT_TYPE *)lookup(&dtd.elementTypes, tagNamePtr->str,0);
    if (!elementType) {
      tagNamePtr->str = poolCopyString(&dtd.pool, tagNamePtr->str);
      if (!tagNamePtr->str)
	return XML_ERROR_NO_MEMORY;
      elementType = (ELEMENT_TYPE *)lookup(&dtd.elementTypes, tagNamePtr->str, sizeof(ELEMENT_TYPE));
      if (!elementType)
        return XML_ERROR_NO_MEMORY;
      if (ns && !setElementTypePrefix(parser, elementType))
        return XML_ERROR_NO_MEMORY;
    }
    nDefaultAtts = elementType->nDefaultAtts;
  }
  /* get the attributes from the tokenizer */
  n = XmlGetAttributes(enc, attStr, attsSize, atts);
  if (n + nDefaultAtts > attsSize) {
    int oldAttsSize = attsSize;
    attsSize = n + nDefaultAtts + INIT_ATTS_SIZE;
    atts = REALLOC((void *)atts, attsSize * sizeof(ATTRIBUTE));
    if (!atts)
      return XML_ERROR_NO_MEMORY;
    if (n > oldAttsSize)
      XmlGetAttributes(enc, attStr, n, atts);
  }
  appAtts = (const XML_Char **)atts;
  for (i = 0; i < n; i++) {
    /* add the name and value to the attribute list */
    ATTRIBUTE_ID *attId = getAttributeId(parser, enc, atts[i].name,
					 atts[i].name
					 + XmlNameLength(enc, atts[i].name));
    if (!attId)
      return XML_ERROR_NO_MEMORY;
    /* detect duplicate attributes */
    if ((attId->name)[-1]) {
      if (enc == encoding)
	eventPtr = atts[i].name;
      return XML_ERROR_DUPLICATE_ATTRIBUTE;
    }
    (attId->name)[-1] = 1;
    appAtts[attIndex++] = attId->name;
    if (!atts[i].normalized) {
      enum XML_Error result;
      int isCdata = 1;

      /* figure out whether declared as other than CDATA */
      if (attId->maybeTokenized) {
	int j;
	for (j = 0; j < nDefaultAtts; j++) {
	  if (attId == elementType->defaultAtts[j].id) {
	    isCdata = elementType->defaultAtts[j].isCdata;
	    break;
	  }
	}
      }

      /* normalize the attribute value */
      result = storeAttributeValue(parser, enc, isCdata,
				   atts[i].valuePtr, atts[i].valueEnd,
			           &tempPool);
      if (result)
	return result;
      if (tagNamePtr) {
	appAtts[attIndex] = poolStart(&tempPool);
	poolFinish(&tempPool);
      }
      else
	poolDiscard(&tempPool);
    }
    else if (tagNamePtr) {
      /* the value did not need normalizing */
      appAtts[attIndex] = poolStoreString(&tempPool, enc, atts[i].valuePtr, atts[i].valueEnd);
      if (appAtts[attIndex] == 0)
	return XML_ERROR_NO_MEMORY;
      poolFinish(&tempPool);
    }
    /* handle prefixed attribute names */
    if (attId->prefix && tagNamePtr) {
      if (attId->xmlns) {
	/* deal with namespace declarations here */
        if (!addBinding(parser, attId->prefix, attId, appAtts[attIndex], bindingsPtr))
          return XML_ERROR_NO_MEMORY;
        --attIndex;
      }
      else {
	/* deal with other prefixed names later */
        attIndex++;
        nPrefixes++;
        (attId->name)[-1] = 2;
      }
    }
    else
      attIndex++;
  }
  if (tagNamePtr) {
    int j;
    nSpecifiedAtts = attIndex;
    if (elementType->idAtt && (elementType->idAtt->name)[-1]) {
      for (i = 0; i < attIndex; i += 2)
	if (appAtts[i] == elementType->idAtt->name) {
	  idAttIndex = i;
	  break;
	}
    }
    else
      idAttIndex = -1;
    /* do attribute defaulting */
    for (j = 0; j < nDefaultAtts; j++) {
      const DEFAULT_ATTRIBUTE *da = elementType->defaultAtts + j;
      if (!(da->id->name)[-1] && da->value) {
        if (da->id->prefix) {
          if (da->id->xmlns) {
	    if (!addBinding(parser, da->id->prefix, da->id, da->value, bindingsPtr))
	      return XML_ERROR_NO_MEMORY;
	  }
          else {
	    (da->id->name)[-1] = 2;
	    nPrefixes++;
 