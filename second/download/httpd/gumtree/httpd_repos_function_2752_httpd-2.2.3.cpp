static enum XML_Error
processXmlDecl(XML_Parser parser, int isGeneralTextEntity,
	       const char *s, const char *next)
{
  const char *encodingName = 0;
  const char *storedEncName = 0;
  const ENCODING *newEncoding = 0;
  const char *version = 0;
  const char *versionend;
  const char *storedversion = 0;
  int standalone = -1;
  if (!(ns
        ? XmlParseXmlDeclNS
	: XmlParseXmlDecl)(isGeneralTextEntity,
		           encoding,
		           s,
		           next,
		           &eventPtr,
		           &version,
			   &versionend,
		           &encodingName,
		           &newEncoding,
		           &standalone))
    return XML_ERROR_SYNTAX;
  if (!isGeneralTextEntity && standalone == 1) {
    dtd.standalone = 1;
#ifdef XML_DTD
    if (paramEntityParsing == XML_PARAM_ENTITY_PARSING_UNLESS_STANDALONE)
      paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif /* XML_DTD */
  }
  if (xmlDeclHandler) {
    if (encodingName) {
      storedEncName = poolStoreString(&temp2Pool,
				      encoding,
				      encodingName,
				      encodingName
				      + XmlNameLength(encoding, encodingName));
      if (! storedEncName)
	return XML_ERROR_NO_MEMORY;
      poolFinish(&temp2Pool);
    }
    if (version) {
      storedversion = poolStoreString(&temp2Pool,
				      encoding,
				      version,
				      versionend - encoding->minBytesPerChar);
      if (! storedversion)
	return XML_ERROR_NO_MEMORY;
    }
    xmlDeclHandler(handlerArg, storedversion, storedEncName, standalone);
  }
  else if (defaultHandler)
    reportDefault(parser, encoding, s, next);
  if (!protocolEncodingName) {
    if (newEncoding) {
      if (newEncoding->minBytesPerChar != encoding->minBytesPerChar) {
	eventPtr = encodingName;
	return XML_ERROR_INCORRECT_ENCODING;
      }
      encoding = newEncoding;
    }
    else if (encodingName) {
      enum XML_Error result;
      if (! storedEncName) {
	storedEncName = poolStoreString(&temp2Pool,
					encoding,
					encodingName,
					encodingName
					+ XmlNameLength(encoding, encodingName));
	if (! storedEncName)
	  return XML_ERROR_NO_MEMORY;
      }
      result = handleUnknownEncoding(parser, storedEncName);
      poolClear(&tempPool);
      if (result == XML_ERROR_UNKNOWN_ENCODING)
	eventPtr = encodingName;
      return result;
    }
  }

  if (storedEncName || storedversion)
    poolClear(&temp2Pool);

  return XML_ERROR_NONE;
}