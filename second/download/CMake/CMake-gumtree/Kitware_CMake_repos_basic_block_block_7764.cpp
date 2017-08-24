(n + nDefaultAtts > attsSize) {
    int oldAttsSize = attsSize;
    ATTRIBUTE *temp;
#ifdef XML_ATTR_INFO
    XML_AttrInfo *temp2;
#endif
    attsSize = n + nDefaultAtts + INIT_ATTS_SIZE;
    temp = (ATTRIBUTE *)REALLOC((void *)atts, attsSize * sizeof(ATTRIBUTE));
    if (temp == NULL)
      return XML_ERROR_NO_MEMORY;
    atts = temp;
#ifdef XML_ATTR_INFO
    temp2 = (XML_AttrInfo *)REALLOC((void *)attInfo, attsSize * sizeof(XML_AttrInfo));
    if (temp2 == NULL)
      return XML_ERROR_NO_MEMORY;
    attInfo = temp2;
#endif
    if (n > oldAttsSize)
      XmlGetAttributes(enc, attStr, n, atts);
  }