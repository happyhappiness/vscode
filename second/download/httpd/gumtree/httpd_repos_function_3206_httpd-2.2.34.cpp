static enum XML_Error
storeAtts(XML_Parser parser, const ENCODING *enc,
          const char *attStr, TAG_NAME *tagNamePtr,
          BINDING **bindingsPtr)
{
  DTD * const dtd = _dtd;  /* save one level of indirection */
  ELEMENT_TYPE *elementType;
  int nDefaultAtts;
  const XML_Char **appAtts;   /* the attribute list for the application */
  int attIndex = 0;
  int prefixLen;
  int i;
  int n;
  XML_Char *uri;
  int nPrefixes = 0;
  BINDING *binding;
  const XML_Char *localPart;

  /* lookup the element type name */
  elementType = (ELEMENT_TYPE *)lookup(&dtd->elementTypes, tagNamePtr->str,0);
  if (!elementType) {
    const XML_Char *name = poolCopyString(&dtd->pool, tagNamePtr->str);
    if (!name)
      return XML_ERROR_NO_MEMORY;
    elementType = (ELEMENT_TYPE *)lookup(&dtd->elementTypes, name,
                                         sizeof(ELEMENT_TYPE));
    if (!elementType)
      return XML_ERROR_NO_MEMORY;
    if (ns && !setElementTypePrefix(parser, elementType))
      return XML_ERROR_NO_MEMORY;
  }
  nDefaultAtts = elementType->nDefaultAtts;

  /* get the attributes from the tokenizer */
  n = XmlGetAttributes(enc, attStr, attsSize, atts);
  if (n + nDefaultAtts > attsSize) {
    int oldAttsSize = attsSize;
    ATTRIBUTE *temp;
    attsSize = n + nDefaultAtts + INIT_ATTS_SIZE;
    temp = (ATTRIBUTE *)REALLOC((void *)atts, attsSize * sizeof(ATTRIBUTE));
    if (temp == NULL)
      return XML_ERROR_NO_MEMORY;
    atts = temp;
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
    /* Detect duplicate attributes by their QNames. This does not work when
       namespace processing is turned on and different prefixes for the same
       namespace are used. For this case we have a check further down.
    */
    if ((attId->name)[-1]) {
      if (enc == encoding)
        eventPtr = atts[i].name;
      return XML_ERROR_DUPLICATE_ATTRIBUTE;
    }
    (attId->name)[-1] = 1;
    appAtts[attIndex++] = attId->name;
    if (!atts[i].normalized) {
      enum XML_Error result;
      XML_Bool isCdata = XML_TRUE;

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
      appAtts[attIndex] = poolStart(&tempPool);
      poolFinish(&tempPool);
    }
    else {
      /* the value did not need normalizing */
      appAtts[attIndex] = poolStoreString(&tempPool, enc, atts[i].valuePtr,
                                          atts[i].valueEnd);
      if (appAtts[attIndex] == 0)
        return XML_ERROR_NO_MEMORY;
      poolFinish(&tempPool);
    }
    /* handle prefixed attribute names */
    if (attId->prefix) {
      if (attId->xmlns) {
        /* deal with namespace declarations here */
        enum XML_Error result = addBinding(parser, attId->prefix, attId,
                                           appAtts[attIndex], bindingsPtr);
        if (result)
          return result;
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

  /* set-up for XML_GetSpecifiedAttributeCount and XML_GetIdAttributeIndex */
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
  for (i = 0; i < nDefaultAtts; i++) {
    const DEFAULT_ATTRIBUTE *da = elementType->defaultAtts + i;
    if (!(da->id->name)[-1] && da->value) {
      if (da->id->prefix) {
        if (da->id->xmlns) {
          enum XML_Error result = addBinding(parser, da->id->prefix, da->id,
                                             da->value, bindingsPtr);
          if (result)
            return result;
        }
        else {
          (da->id->name)[-1] = 2;
          nPrefixes++;
          appAtts[attIndex++] = da->id->name;
          appAtts[attIndex++] = da->value;
        }
      }
      else {
        (da->id->name)[-1] = 1;
        appAtts[attIndex++] = da->id->name;
        appAtts[attIndex++] = da->value;
      }
    }
  }
  appAtts[attIndex] = 0;

  /* expand prefixed attribute names, check for duplicates,
     and clear flags that say whether attributes were specified */
  i = 0;
  if (nPrefixes) {
    int j;  /* hash table index */
    unsigned long version = nsAttsVersion;
    int nsAttsSize = (int)1 << nsAttsPower;
    /* size of hash table must be at least 2 * (# of prefixed attributes) */
    if ((nPrefixes << 1) >> nsAttsPower) {  /* true for nsAttsPower = 0 */
      NS_ATT *temp;
      /* hash table size must also be a power of 2 and >= 8 */
      while (nPrefixes >> nsAttsPower++);
      if (nsAttsPower < 3)
        nsAttsPower = 3;
      nsAttsSize = (int)1 << nsAttsPower;
      temp = (NS_ATT *)REALLOC(nsAtts, nsAttsSize * sizeof(NS_ATT));
      if (!temp)
        return XML_ERROR_NO_MEMORY;
      nsAtts = temp;
      version = 0;  /* force re-initialization of nsAtts hash table */
    }
    /* using a version flag saves us from initializing nsAtts every time */
    if (!version) {  /* initialize version flags when version wraps around */
      version = INIT_ATTS_VERSION;
      for (j = nsAttsSize; j != 0; )
        nsAtts[--j].version = version;
    }
    nsAttsVersion = --version;

    /* expand prefixed names and check for duplicates */
    for (; i < attIndex; i += 2) {
      const XML_Char *s = appAtts[i];
      if (s[-1] == 2) {  /* prefixed */
        ATTRIBUTE_ID *id;
        const BINDING *b;
        unsigned long uriHash = 0;
        ((XML_Char *)s)[-1] = 0;  /* clear flag */
        id = (ATTRIBUTE_ID *)lookup(&dtd->attributeIds, s, 0);
        b = id->prefix->binding;
        if (!b)
          return XML_ERROR_UNBOUND_PREFIX;

        /* as we expand the name we also calculate its hash value */
        for (j = 0; j < b->uriLen; j++) {
          const XML_Char c = b->uri[j];
          if (!poolAppendChar(&tempPool, c))
            return XML_ERROR_NO_MEMORY;
          uriHash = CHAR_HASH(uriHash, c);
        }
        while (*s++ != XML_T(':'))
          ;
        do {  /* copies null terminator */
          const XML_Char c = *s;
          if (!poolAppendChar(&tempPool, *s))
            return XML_ERROR_NO_MEMORY;
          uriHash = CHAR_HASH(uriHash, c);
        } while (*s++);

        { /* Check hash table for duplicate of expanded name (uriName).
             Derived from code in lookup(HASH_TABLE *table, ...).
          */
          unsigned char step = 0;
          unsigned long mask = nsAttsSize - 1;
          j = uriHash & mask;  /* index into hash table */
          while (nsAtts[j].version == version) {
            /* for speed we compare stored hash values first */
            if (uriHash == nsAtts[j].hash) {
              const XML_Char *s1 = poolStart(&tempPool);
              const XML_Char *s2 = nsAtts[j].uriName;
              /* s1 is null terminated, but not s2 */
              for (; *s1 == *s2 && *s1 != 0; s1++, s2++);
              if (*s1 == 0)
                return XML_ERROR_DUPLICATE_ATTRIBUTE;
            }
            if (!step)
              step = PROBE_STEP(uriHash, mask, nsAttsPower);
            j < step ? ( j += nsAttsSize - step) : 