static enum XML_Error
handleUnknownEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (unknownEncodingHandler) {
    XML_Encoding info;
    int i;
    for (i = 0; i < 256; i++)
      info.map[i] = -1;
    info.convert = 0;
    info.data = 0;
    info.release = 0;
    if (unknownEncodingHandler(unknownEncodingHandlerData, encodingName, &info)) {
      ENCODING *enc;
      unknownEncodingMem = MALLOC(XmlSizeOfUnknownEncoding());
      if (!unknownEncodingMem) {
	if (info.release)
	  info.release(info.data);
	return XML_ERROR_NO_MEMORY;
      }
      enc = (ns
	     ? XmlInitUnknownEncodingNS
	     : XmlInitUnknownEncoding)(unknownEncodingMem,
				       info.map,
				       info.convert,
				       info.data);
      if (enc) {
	unknownEncodingData = info.data;
	unknownEncodingRelease = info.release;
	encoding = enc;
	return XML_ERROR_NONE;
      }
    }
    if (info.release)
      info.release(info.data);
  }
  return XML_ERROR_UNKNOWN_ENCODING;
}