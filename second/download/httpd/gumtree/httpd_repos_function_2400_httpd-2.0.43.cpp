XML_Parser
XML_ParserCreate_MM(const XML_Char *encodingName,
		    const XML_Memory_Handling_Suite *memsuite,
		    const XML_Char *nameSep) {
  
  XML_Parser parser;
  static
  const XML_Char implicitContext[] = {
    XML_T('x'), XML_T('m'), XML_T('l'), XML_T('='),
    XML_T('h'), XML_T('t'), XML_T('t'), XML_T('p'), XML_T(':'),
    XML_T('/'), XML_T('/'), XML_T('w'), XML_T('w'), XML_T('w'),
    XML_T('.'), XML_T('w'), XML_T('3'),
    XML_T('.'), XML_T('o'), XML_T('r'), XML_T('g'),
    XML_T('/'), XML_T('X'), XML_T('M'), XML_T('L'),
    XML_T('/'), XML_T('1'), XML_T('9'), XML_T('9'), XML_T('8'),
    XML_T('/'), XML_T('n'), XML_T('a'), XML_T('m'), XML_T('e'),
    XML_T('s'), XML_T('p'), XML_T('a'), XML_T('c'), XML_T('e'),
    XML_T('\0')
  };


  if (memsuite) {
    XML_Memory_Handling_Suite *mtemp;
    parser = memsuite->malloc_fcn(sizeof(Parser));
    mtemp = &(((Parser *) parser)->m_mem);
    mtemp->malloc_fcn = memsuite->malloc_fcn;
    mtemp->realloc_fcn = memsuite->realloc_fcn;
    mtemp->free_fcn = memsuite->free_fcn;
  }
  else {
    XML_Memory_Handling_Suite *mtemp;
    parser = malloc(sizeof(Parser));
    mtemp = &(((Parser *) parser)->m_mem);
    mtemp->malloc_fcn = malloc;
    mtemp->realloc_fcn = realloc;
    mtemp->free_fcn = free;
  }

  if (!parser)
    return parser;
  processor = prologInitProcessor;
  XmlPrologStateInit(&prologState);
  userData = 0;
  handlerArg = 0;
  startElementHandler = 0;
  endElementHandler = 0;
  characterDataHandler = 0;
  processingInstructionHandler = 0;
  commentHandler = 0;
  startCdataSectionHandler = 0;
  endCdataSectionHandler = 0;
  defaultHandler = 0;
  startDoctypeDeclHandler = 0;
  endDoctypeDeclHandler = 0;
  unparsedEntityDeclHandler = 0;
  notationDeclHandler = 0;
  startNamespaceDeclHandler = 0;
  endNamespaceDeclHandler = 0;
  notStandaloneHandler = 0;
  externalEntityRefHandler = 0;
  externalEntityRefHandlerArg = parser;
  unknownEncodingHandler = 0;
  elementDeclHandler = 0;
  attlistDeclHandler = 0;
  entityDeclHandler = 0;
  xmlDeclHandler = 0;
  buffer = 0;
  bufferPtr = 0;
  bufferEnd = 0;
  parseEndByteIndex = 0;
  parseEndPtr = 0;
  bufferLim = 0;
  declElementType = 0;
  declAttributeId = 0;
  declEntity = 0;
  doctypeName = 0;
  doctypeSysid = 0;
  doctypePubid = 0;
  declAttributeType = 0;
  declNotationName = 0;
  declNotationPublicId = 0;
  memset(&position, 0, sizeof(POSITION));
  errorCode = XML_ERROR_NONE;
  eventPtr = 0;
  eventEndPtr = 0;
  positionPtr = 0;
  openInternalEntities = 0;
  tagLevel = 0;
  tagStack = 0;
  freeTagList = 0;
  freeBindingList = 0;
  inheritedBindings = 0;
  attsSize = INIT_ATTS_SIZE;
  atts = MALLOC(attsSize * sizeof(ATTRIBUTE));
  nSpecifiedAtts = 0;
  dataBuf = MALLOC(INIT_DATA_BUF_SIZE * sizeof(XML_Char));
  groupSize = 0;
  groupConnector = 0;
  hadExternalDoctype = 0;
  unknownEncodingMem = 0;
  unknownEncodingRelease = 0;
  unknownEncodingData = 0;
  unknownEncodingHandlerData = 0;
  namespaceSeparator = '!';
#ifdef XML_DTD
  parentParser = 0;
  paramEntityParsing = XML_PARAM_ENTITY_PARSING_NEVER;
#endif
  ns = 0;
  ns_triplets = 0;
  poolInit(&tempPool, &(((Parser *) parser)->m_mem));
  poolInit(&temp2Pool, &(((Parser *) parser)->m_mem));
  protocolEncodingName = encodingName ? poolCopyString(&tempPool, encodingName) : 0;
  curBase = 0;
  if (!dtdInit(&dtd, parser) || !atts || !dataBuf
      || (encodingName && !protocolEncodingName)) {
    XML_ParserFree(parser);
    return 0;
  }
  dataBufEnd = dataBuf + INIT_DATA_BUF_SIZE;

  if (nameSep) {
    XmlInitEncodingNS(&initEncoding, &encoding, 0);
    ns = 1;
    internalEncoding = XmlGetInternalEncodingNS();
    namespaceSeparator = *nameSep;

    if (! setContext(parser, implicitContext)) {
      XML_ParserFree(parser);
      return 0;
    }
  }
  else {
    XmlInitEncoding(&initEncoding, &encoding, 0);
    internalEncoding = XmlGetInternalEncoding();
  }

  return parser;
}