{
    ATTRIBUTE *currAtt = &atts[i];
#ifdef XML_ATTR_INFO
    XML_AttrInfo *currAttInfo = &attInfo[i];
#endif
    /* add the name and value to the attribute list */
    ATTRIBUTE_ID *attId = getAttributeId(parser, enc, currAtt->name,
                                         currAtt->name
                                         + XmlNameLength(enc, currAtt->name));
    if (!attId)
      return XML_ERROR_NO_MEMORY;
#ifdef XML_ATTR_INFO
    currAttInfo->nameStart = parseEndByteIndex - (parseEndPtr - currAtt->name);
    currAttInfo->nameEnd = currAttInfo->nameStart +
                           XmlNameLength(enc, currAtt->name);
    currAttInfo->valueStart = parseEndByteIndex -
                            (parseEndPtr - currAtt->valuePtr);
    currAttInfo->valueEnd = parseEndByteIndex - (parseEndPtr - currAtt->valueEnd);
#endif
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