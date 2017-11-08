XML_Parser XML_ExternalEntityParserCreate(XML_Parser oldParser,
					  const XML_Char *context,
					  const XML_Char *encodingName)
{
  XML_Parser parser = oldParser;
  DTD *oldDtd = &dtd;
  XML_StartElementHandler oldStartElementHandler = startElementHandler;
  XML_EndElementHandler oldEndElementHandler = endElementHandler;
  XML_CharacterDataHandler oldCharacterDataHandler = characterDataHandler;
  XML_ProcessingInstructionHandler oldProcessingInstructionHandler = processingInstructionHandler;
  XML_CommentHandler oldCommentHandler = commentHandler;
  XML_StartCdataSectionHandler oldStartCdataSectionHandler = startCdataSectionHandler;
  XML_EndCdataSectionHandler oldEndCdataSectionHandler = endCdataSectionHandler;
  XML_DefaultHandler oldDefaultHandler = defaultHandler;
  XML_UnparsedEntityDeclHandler oldUnparsedEntityDeclHandler = unparsedEntityDeclHandler;
  XML_NotationDeclHandler oldNotationDeclHandler = notationDeclHandler;
  XML_StartNamespaceDeclHandler oldStartNamespaceDeclHandler = startNamespaceDeclHandler;
  XML_EndNamespaceDeclHandler oldEndNamespaceDeclHandler = endNamespaceDeclHandler;
  XML_NotStandaloneHandler oldNotStandaloneHandler = notStandaloneHandler;
  XML_ExternalEntityRefHandler oldExternalEntityRefHandler = externalEntityRefHandler;
  XML_UnknownEncodingHandler oldUnknownEncodingHandler = unknownEncodingHandler;
  XML_ElementDeclHandler oldElementDeclHandler = elementDeclHandler;
  XML_AttlistDeclHandler oldAttlistDeclHandler = attlistDeclHandler;
  XML_EntityDeclHandler oldEntityDeclHandler = entityDeclHandler;
  XML_XmlDeclHandler oldXmlDeclHandler = xmlDeclHandler;
  ELEMENT_TYPE * oldDeclElementType = declElementType;

  void *oldUserData = userData;
  void *oldHandlerArg = handlerArg;
  int oldDefaultExpandInternalEntities = defaultExpandInternalEntities;
  void *oldExternalEntityRefHandlerArg = externalEntityRefHandlerArg;
#ifdef XML_DTD
  int oldParamEntityParsing = paramEntityParsing;
#endif
  int oldns_triplets = ns_triplets;

  if (ns) {
    XML_Char tmp[2];

    *tmp = namespaceSeparator;
    parser = XML_ParserCreate_MM(encodingName, &((Parser *)parser)->m_mem,
				 tmp);
  }
  else {
    parser = XML_ParserCreate_MM(encodingName, &((Parser *)parser)->m_mem,
				 NULL);
  }

  if (!parser)
    return 0;

  startElementHandler = oldStartElementHandler;
  endElementHandler = oldEndElementHandler;
  characterDataHandler = oldCharacterDataHandler;
  processingInstructionHandler = oldProcessingInstructionHandler;
  commentHandler = oldCommentHandler;
  startCdataSectionHandler = oldStartCdataSectionHandler;
  endCdataSectionHandler = oldEndCdataSectionHandler;
  defaultHandler = oldDefaultHandler;
  unparsedEntityDeclHandler = oldUnparsedEntityDeclHandler;
  notationDeclHandler = oldNotationDeclHandler;
  startNamespaceDeclHandler = oldStartNamespaceDeclHandler;
  endNamespaceDeclHandler = oldEndNamespaceDeclHandler;
  notStandaloneHandler = oldNotStandaloneHandler;
  externalEntityRefHandler = oldExternalEntityRefHandler;
  unknownEncodingHandler = oldUnknownEncodingHandler;
  elementDeclHandler = oldElementDeclHandler;
  attlistDeclHandler = oldAttlistDeclHandler;
  entityDeclHandler = oldEntityDeclHandler;
  xmlDeclHandler = oldXmlDeclHandler;
  declElementType = oldDeclElementType;
  userData = oldUserData;
  if (oldUserData == oldHandlerArg)
    handlerArg = userData;
  else
    handlerArg = parser;
  if (oldExternalEntityRefHandlerArg != oldParser)
    externalEntityRefHandlerArg = oldExternalEntityRefHandlerArg;
  defaultExpandInternalEntities = oldDefaultExpandInternalEntities;
  ns_triplets = oldns_triplets;
#ifdef XML_DTD
  paramEntityParsing = oldParamEntityParsing;
  if (context) {
#endif /* XML_DTD */
    if (!dtdCopy(&dtd, oldDtd, parser) || !setContext(parser, context)) {
      XML_ParserFree(parser);
      return 0;
    }
    processor = externalEntityInitProcessor;
#ifdef XML_DTD
  }
  else {
    dtdSwap(&dtd, oldDtd);
    parentParser = oldParser;
    XmlPrologStateInitExternalEntity(&prologState);
    dtd.complete = 1;
    hadExternalDoctype = 1;
  }
#endif /* XML_DT