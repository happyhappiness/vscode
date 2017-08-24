(nameSep) {
    ns = XML_TRUE;
    internalEncoding = XmlGetInternalEncodingNS();
    namespaceSeparator = *nameSep;
  }
  else {
    internalEncoding = XmlGetInternalEncoding();
  }