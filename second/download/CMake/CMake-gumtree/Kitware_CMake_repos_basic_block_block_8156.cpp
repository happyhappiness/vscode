{
    int i;
    ELEMENT_TYPE *newE;
    const XML_Char *name;
    const ELEMENT_TYPE *oldE = (ELEMENT_TYPE *)hashTableIterNext(&iter);
    if (!oldE)
      break;
    name = poolCopyString(&(newDtd->pool), oldE->name);
    if (!name)
      return 0;
    newE = (ELEMENT_TYPE *)lookup(oldParser, &(newDtd->elementTypes), name,
                                  sizeof(ELEMENT_TYPE));
    if (!newE)
      return 0;
    if (oldE->nDefaultAtts) {
      newE->defaultAtts = (DEFAULT_ATTRIBUTE *)
          ms->malloc_fcn(oldE->nDefaultAtts * sizeof(DEFAULT_ATTRIBUTE));
      if (!newE->defaultAtts) {
        return 0;
      }
    }
    if (oldE->idAtt)
      newE->idAtt = (ATTRIBUTE_ID *)
          lookup(oldParser, &(newDtd->attributeIds), oldE->idAtt->name, 0);
    newE->allocDefaultAtts = newE->nDefaultAtts = oldE->nDefaultAtts;
    if (oldE->prefix)
      newE->prefix = (PREFIX *)lookup(oldParser, &(newDtd->prefixes),
                                      oldE->prefix->name, 0);
    for (i = 0; i < newE->nDefaultAtts; i++) {
      newE->defaultAtts[i].id = (ATTRIBUTE_ID *)
          lookup(oldParser, &(newDtd->attributeIds), oldE->defaultAtts[i].id->name, 0);
      newE->defaultAtts[i].isCdata = oldE->defaultAtts[i].isCdata;
      if (oldE->defaultAtts[i].value) {
        newE->defaultAtts[i].value
            = poolCopyString(&(newDtd->pool), oldE->defaultAtts[i].value);
        if (!newE->defaultAtts[i].value)
          return 0;
      }
      else
        newE->defaultAtts[i].value = NULL;
    }
  }