static enum XML_Error
doProlog(XML_Parser parser,
	 const ENCODING *enc,
	 const char *s,
	 const char *end,
	 int tok,
	 const char *next,
	 const char **nextPtr)
{
#ifdef XML_DTD
  static const XML_Char externalSubsetName[] = { '#' , '\0' };
#endif /* XML_DTD */

  const char **eventPP;
  const char **eventEndPP;
  enum XML_Content_Quant quant;

  if (enc == encoding) {
    eventPP = &eventPtr;
    eventEndPP = &eventEndPtr;
  }
  else {
    eventPP = &(openInternalEntities->internalEventPtr);
    eventEndPP = &(openInternalEntities->internalEventEndPtr);
  }
  for (;;) {
    int role;
    *eventPP = s;
    *eventEndPP = next;
    if (tok <= 0) {
      if (nextPtr != 0 && tok != XML_TOK_INVALID) {
	*nextPtr = s;
	return XML_ERROR_NONE;
      }
      switch (tok) {
      case XML_TOK_INVALID:
	*eventPP = next;
	return XML_ERROR_INVALID_TOKEN;
      case XML_TOK_PARTIAL:
	return XML_ERROR_UNCLOSED_TOKEN;
      case XML_TOK_PARTIAL_CHAR:
	return XML_ERROR_PARTIAL_CHAR;
      case XML_TOK_NONE:
#ifdef XML_DTD
	if (enc != encoding)
	  return XML_ERROR_NONE;
	if (parentParser) {
	  if (XmlTokenRole(&prologState, XML_TOK_NONE, end, end, enc)
	      == XML_ROLE_ERROR)
	    return XML_ERROR_SYNTAX;
	  hadExternalDoctype = 0;
	  return XML_ERROR_NONE;
	}
#endif /* XML_DTD */
	return XML_ERROR_NO_ELEMENTS;
      default:
	tok = -tok;
	next = end;
	break;
      }
    }
    role = XmlTokenRole(&prologState, tok, s, next, enc);
    switch (role) {
    case XML_ROLE_XML_DECL:
      {
	enum XML_Error result = processXmlDecl(parser, 0, s, next);
	if (result != XML_ERROR_NONE)
	  return result;
	enc = encoding;
      }
      break;
    case XML_ROLE_DOCTYPE_NAME:
      if (startDoctypeDeclHandler) {
	doctypeName = poolStoreString(&tempPool, enc, s, next);
	if (! doctypeName)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&tempPool);
	doctypeSysid = 0;
	doctypePubid = 0;
      }
      break;
    case XML_ROLE_DOCTYPE_INTERNAL_SUBSET:
      if (startDoctypeDeclHandler) {
	startDoctypeDeclHandler(handlerArg, doctypeName, doctypeSysid,
				doctypePubid, 1);
	doctypeName = 0;
	poolClear(&tempPool);
      }
      break;
#ifdef XML_DTD
    case XML_ROLE_TEXT_DECL:
      {
	enum XML_Error result = processXmlDecl(parser, 1, s, next);
	if (result != XML_ERROR_NONE)
	  return result;
	enc = encoding;
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_DOCTYPE_PUBLIC_ID:
      if (startDoctypeDeclHandler) {
	doctypePubid = poolStoreString(&tempPool, enc, s + 1, next - 1);
	if (! doctypePubid)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&tempPool);
      }
#ifdef XML_DTD
      declEntity = (ENTITY *)lookup(&dtd.paramEntities,
				    externalSubsetName,
				    sizeof(ENTITY));
      if (!declEntity)
	return XML_ERROR_NO_MEMORY;
#endif /* XML_DTD */
      /* fall through */
    case XML_ROLE_ENTITY_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
	return XML_ERROR_SYNTAX;
      if (declEntity) {
	XML_Char *tem = poolStoreString(&dtd.pool,
	                                enc,
					s + enc->minBytesPerChar,
	  				next - enc->minBytesPerChar);
	if (!tem)
	  return XML_ERROR_NO_MEMORY;
	normalizePublicId(tem);
	declEntity->publicId = tem;
	poolFinish(&dtd.pool);
      }
      break;
    case XML_ROLE_DOCTYPE_CLOSE:
      if (doctypeName) {
	startDoctypeDeclHandler(handlerArg, doctypeName,
				doctypeSysid, doctypePubid, 0);
	poolClear(&tempPool);
      }
      if (dtd.complete && hadExternalDoctype) {
	dtd.complete = 0;
#ifdef XML_DTD
	if (paramEntityParsing && externalEntityRefHandler) {
	  ENTITY *entity = (ENTITY *)lookup(&dtd.paramEntities,
					    externalSubsetName,
					    0);
	  if (!externalEntityRefHandler(externalEntityRefHandlerArg,
					0,
					entity->base,
					entity->systemId,
					entity->publicId))
	   return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
	}
#endif /* XML_DTD */
	if (!dtd.complete
	    && !dtd.standalone
	    && notStandaloneHandler
	    && !notStandaloneHandler(handlerArg))
	  return XML_ERROR_NOT_STANDALONE;
      }
      if (endDoctypeDeclHandler)
	endDoctypeDeclHandler(handlerArg);
      break;
    case XML_ROLE_INSTANCE_START:
      processor = contentProcessor;
      return contentProcessor(parser, s, end, nextPtr);
    case XML_ROLE_ATTLIST_ELEMENT_NAME:
      declElementType = getElementType(parser, enc, s, next);
      if (!declElementType)
	return XML_ERROR_NO_MEMORY;
      break;
    case XML_ROLE_ATTRIBUTE_NAME:
      declAttributeId = getAttributeId(parser, enc, s, next);
      if (!declAttributeId)
	return XML_ERROR_NO_MEMORY;
      declAttributeIsCdata = 0;
      declAttributeType = 0;
      declAttributeIsId = 0;
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_CDATA:
      declAttributeIsCdata = 1;
      declAttributeType = "CDATA";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_ID:
      declAttributeIsId = 1;
      declAttributeType = "ID";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREF:
      declAttributeType = "IDREF";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_IDREFS:
      declAttributeType = "IDREFS";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITY:
      declAttributeType = "ENTITY";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_ENTITIES:
      declAttributeType = "ENTITIES";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKEN:
      declAttributeType = "NMTOKEN";
      break;
    case XML_ROLE_ATTRIBUTE_TYPE_NMTOKENS:
      declAttributeType = "NMTOKENS";
      break;

    case XML_ROLE_ATTRIBUTE_ENUM_VALUE:
    case XML_ROLE_ATTRIBUTE_NOTATION_VALUE:
      if (attlistDeclHandler)
      {
	char *prefix;
	if (declAttributeType) {
	  prefix = "|";
	}
	else {
	  prefix = (role == XML_ROLE_ATTRIBUTE_NOTATION_VALUE
		    ? "NOTATION("
		    : "(");
	}
	if (! poolAppendString(&tempPool, prefix))
	  return XML_ERROR_NO_MEMORY;
	if (! poolAppend(&tempPool, enc, s, next))
	  return XML_ERROR_NO_MEMORY;
	declAttributeType = tempPool.start;
      }
      break;
    case XML_ROLE_IMPLIED_ATTRIBUTE_VALUE:
    case XML_ROLE_REQUIRED_ATTRIBUTE_VALUE:
      if (dtd.complete
	  && !defineAttribute(declElementType, declAttributeId,
			      declAttributeIsCdata, declAttributeIsId, 0,
			      parser))
	return XML_ERROR_NO_MEMORY;
      if (attlistDeclHandler && declAttributeType) {
	if (*declAttributeType == '('
	    || (*declAttributeType == 'N' && declAttributeType[1] == 'O')) {
	  /* Enumerated or Notation type */
	  if (! poolAppendChar(&tempPool, ')')
	      || ! poolAppendChar(&tempPool, '\0'))
	    return XML_ERROR_NO_MEMORY;
	  declAttributeType = tempPool.start;
	  poolFinish(&tempPool);
	}
	*eventEndPP = s;
	attlistDeclHandler(handlerArg, declElementType->name,
			   declAttributeId->name, declAttributeType,
			   0, role == XML_ROLE_REQUIRED_ATTRIBUTE_VALUE);
	poolClear(&tempPool);
      }
      break;
    case XML_ROLE_DEFAULT_ATTRIBUTE_VALUE:
    case XML_ROLE_FIXED_ATTRIBUTE_VALUE:
      {
	const XML_Char *attVal;
	enum XML_Error result
	  = storeAttributeValue(parser, enc, declAttributeIsCdata,
				s + enc->minBytesPerChar,
			        next - enc->minBytesPerChar,
			        &dtd.pool);
	if (result)
	  return result;
	attVal = poolStart(&dtd.pool);
	poolFinish(&dtd.pool);
	if (dtd.complete
	    /* ID attributes aren't allowed to have a default */
	    && !defineAttribute(declElementType, declAttributeId, declAttributeIsCdata, 0, attVal, parser))
	  return XML_ERROR_NO_MEMORY;
	if (attlistDeclHandler && declAttributeType) {
	  if (*declAttributeType == '('
	      || (*declAttributeType == 'N' && declAttributeType[1] == 'O')) {
	    /* Enumerated or Notation type */
	    if (! poolAppendChar(&tempPool, ')')
		|| ! poolAppendChar(&tempPool, '\0'))
	      return XML_ERROR_NO_MEMORY;
	    declAttributeType = tempPool.start;
	    poolFinish(&tempPool);
	  }
	  *eventEndPP = s;
	  attlistDeclHandler(handlerArg, declElementType->name,
			     declAttributeId->name, declAttributeType,
			     attVal,
			     role == XML_ROLE_FIXED_ATTRIBUTE_VALUE);
	  poolClear(&tempPool);
	}
	break;
      }
    case XML_ROLE_ENTITY_VALUE:
      {
	enum XML_Error result = storeEntityValue(parser, enc,
						 s + enc->minBytesPerChar,
						 next - enc->minBytesPerChar);
	if (declEntity) {
	  declEntity->textPtr = poolStart(&dtd.pool);
	  declEntity->textLen = poolLength(&dtd.pool);
	  poolFinish(&dtd.pool);
	  if (entityDeclHandler) {
	    *eventEndPP = s;
	    entityDeclHandler(handlerArg,
			      declEntity->name,
			      declEntity->is_param,
			      declEntity->textPtr,
			      declEntity->textLen,
			      curBase, 0, 0, 0);
	  }
	}
	else
	  poolDiscard(&dtd.pool);
	if (result != XML_ERROR_NONE)
	  return result;
      }
      break;
    case XML_ROLE_DOCTYPE_SYSTEM_ID:
      if (startDoctypeDeclHandler) {
	doctypeSysid = poolStoreString(&tempPool, enc, s + 1, next - 1);
	if (! doctypeSysid)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&tempPool);
      }
      if (!dtd.standalone
#ifdef XML_DTD
	  && !paramEntityParsing
#endif /* XML_DTD */
	  && notStandaloneHandler
	  && !notStandaloneHandler(handlerArg))
	return XML_ERROR_NOT_STANDALONE;
      hadExternalDoctype = 1;
#ifndef XML_DTD
      break;
#else /* XML_DTD */
      if (!declEntity) {
	declEntity = (ENTITY *)lookup(&dtd.paramEntities,
				      externalSubsetName,
				      sizeof(ENTITY));
	declEntity->publicId = 0;
	if (!declEntity)
	  return XML_ERROR_NO_MEMORY;
      }
      /* fall through */
#endif /* XML_DTD */
    case XML_ROLE_ENTITY_SYSTEM_ID:
      if (declEntity) {
	declEntity->systemId = poolStoreString(&dtd.pool, enc,
	                                       s + enc->minBytesPerChar,
	  				       next - enc->minBytesPerChar);
	if (!declEntity->systemId)
	  return XML_ERROR_NO_MEMORY;
	declEntity->base = curBase;
	poolFinish(&dtd.pool);
      }
      break;
    case XML_ROLE_ENTITY_COMPLETE:
      if (declEntity && entityDeclHandler) {
	*eventEndPP = s;
	entityDeclHandler(handlerArg,
			  declEntity->name,
			  0,0,0,
			  declEntity->base,
			  declEntity->systemId,
			  declEntity->publicId,
			  0);
      }
      break;
    case XML_ROLE_ENTITY_NOTATION_NAME:
      if (declEntity) {
	declEntity->notation = poolStoreString(&dtd.pool, enc, s, next);
	if (!declEntity->notation)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&dtd.pool);
	if (unparsedEntityDeclHandler) {
	  *eventEndPP = s;
	  unparsedEntityDeclHandler(handlerArg,
				    declEntity->name,
				    declEntity->base,
				    declEntity->systemId,
				    declEntity->publicId,
				    declEntity->notation);
	}
	else if (entityDeclHandler) {
	  *eventEndPP = s;
	  entityDeclHandler(handlerArg,
			    declEntity->name,
			    0,0,0,
			    declEntity->base,
			    declEntity->systemId,
			    declEntity->publicId,
			    declEntity->notation);
	}
      }
      break;
    case XML_ROLE_GENERAL_ENTITY_NAME:
      {
	const XML_Char *name;
	if (XmlPredefinedEntityName(enc, s, next)) {
	  declEntity = 0;
	  break;
	}
	name = poolStoreString(&dtd.pool, enc, s, next);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	if (dtd.complete) {
	  declEntity = (ENTITY *)lookup(&dtd.generalEntities, name, sizeof(ENTITY));
	  if (!declEntity)
	    return XML_ERROR_NO_MEMORY;
	  if (declEntity->name != name) {
	    poolDiscard(&dtd.pool);
	    declEntity = 0;
	  }
	  else {
	    poolFinish(&dtd.pool);
	    declEntity->publicId = 0;
	    declEntity->is_param = 0;
	  }
	}
	else {
	  poolDiscard(&dtd.pool);
	  declEntity = 0;
	}
      }
      break;
    case XML_ROLE_PARAM_ENTITY_NAME:
#ifdef XML_DTD
      if (dtd.complete) {
	const XML_Char *name = poolStoreString(&dtd.pool, enc, s, next);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	declEntity = (ENTITY *)lookup(&dtd.paramEntities,
				      name, sizeof(ENTITY));
	if (!declEntity)
	  return XML_ERROR_NO_MEMORY;
	if (declEntity->name != name) {
	  poolDiscard(&dtd.pool);
	  declEntity = 0;
	}
	else {
	  poolFinish(&dtd.pool);
	  declEntity->publicId = 0;
	  declEntity->is_param = 1;
	}
      }
#else /* not XML_DTD */
      declEntity = 0;
#endif /* not XML_DTD */
      break;
    case XML_ROLE_NOTATION_NAME:
      declNotationPublicId = 0;
      declNotationName = 0;
      if (notationDeclHandler) {
	declNotationName = poolStoreString(&tempPool, enc, s, next);
	if (!declNotationName)
	  return XML_ERROR_NO_MEMORY;
	poolFinish(&tempPool);
      }
      break;
    case XML_ROLE_NOTATION_PUBLIC_ID:
      if (!XmlIsPublicId(enc, s, next, eventPP))
	return XML_ERROR_SYNTAX;
      if (declNotationName) {
	XML_Char *tem = poolStoreString(&tempPool,
	                                enc,
					s + enc->minBytesPerChar,
	  				next - enc->minBytesPerChar);
	if (!tem)
	  return XML_ERROR_NO_MEMORY;
	normalizePublicId(tem);
	declNotationPublicId = tem;
	poolFinish(&tempPool);
      }
      break;
    case XML_ROLE_NOTATION_SYSTEM_ID:
      if (declNotationName && notationDeclHandler) {
	const XML_Char *systemId
	  = poolStoreString(&tempPool, enc,
			    s + enc->minBytesPerChar,
	  		    next - enc->minBytesPerChar);
	if (!systemId)
	  return XML_ERROR_NO_MEMORY;
	*eventEndPP = s;
	notationDeclHandler(handlerArg,
			    declNotationName,
			    curBase,
			    systemId,
			    declNotationPublicId);
      }
      poolClear(&tempPool);
      break;
    case XML_ROLE_NOTATION_NO_SYSTEM_ID:
      if (declNotationPublicId && notationDeclHandler) {
	*eventEndPP = s;
	notationDeclHandler(handlerArg,
			    declNotationName,
			    curBase,
			    0,
			    declNotationPublicId);
      }
      poolClear(&tempPool);
      break;
    case XML_ROLE_ERROR:
      switch (tok) {
      case XML_TOK_PARAM_ENTITY_REF:
	return XML_ERROR_PARAM_ENTITY_REF;
      case XML_TOK_XML_DECL:
	return XML_ERROR_MISPLACED_XML_PI;
      default:
	return XML_ERROR_SYNTAX;
      }
#ifdef XML_DTD
    case XML_ROLE_IGNORE_SECT:
      {
	enum XML_Error result;
	if (defaultHandler)
	  reportDefault(parser, enc, s, next);
	result = doIgnoreSection(parser, enc, &next, end, nextPtr);
	if (!next) {
	  processor = ignoreSectionProcessor;
	  return result;
	}
      }
      break;
#endif /* XML_DTD */
    case XML_ROLE_GROUP_OPEN:
      if (prologState.level >= groupSize) {
	if (groupSize) {
	  groupConnector = REALLOC(groupConnector, groupSize *= 2);
	  if (dtd.scaffIndex)
	    dtd.scaffIndex = REALLOC(dtd.scaffIndex, groupSize * sizeof(int));
	}
	else
	  groupConnector = MALLOC(groupSize = 32);
	if (!groupConnector)
	  return XML_ERROR_NO_MEMORY;
      }
      groupConnector[prologState.level] = 0;
      if (dtd.in_eldecl) {
	int myindex = nextScaffoldPart(parser);
	if (myindex < 0)
	  return XML_ERROR_NO_MEMORY;
	dtd.scaffIndex[dtd.scaffLevel] = myindex;
	dtd.scaffLevel++;
	dtd.scaffold[myindex].type = XML_CTYPE_SEQ;
      }
      break;
    case XML_ROLE_GROUP_SEQUENCE:
      if (groupConnector[prologState.level] == '|')
	return XML_ERROR_SYNTAX;
      groupConnector[prologState.level] = ',';
      break;
    case XML_ROLE_GROUP_CHOICE:
      if (groupConnector[prologState.level] == ',')
	return XML_ERROR_SYNTAX;
      if (dtd.in_eldecl
	  && ! groupConnector[prologState.level]
	  && dtd.scaffold[dtd.scaffIndex[dtd.scaffLevel - 1]].type != XML_CTYPE_MIXED
	  ) {
	dtd.scaffold[dtd.scaffIndex[dtd.scaffLevel - 1]].type = XML_CTYPE_CHOICE;
      }
      groupConnector[prologState.level] = '|';
      break;
    case XML_ROLE_PARAM_ENTITY_REF:
#ifdef XML_DTD
    case XML_ROLE_INNER_PARAM_ENTITY_REF:
      if (paramEntityParsing
	  && (dtd.complete || role == XML_ROLE_INNER_PARAM_ENTITY_REF)) {
	const XML_Char *name;
	ENTITY *entity;
	name = poolStoreString(&dtd.pool, enc,
				s + enc->minBytesPerChar,
				next - enc->minBytesPerChar);
	if (!name)
	  return XML_ERROR_NO_MEMORY;
	entity = (ENTITY *)lookup(&dtd.paramEntities, name, 0);
	poolDiscard(&dtd.pool);
	if (!entity) {
	  /* FIXME what to do if !dtd.complete? */
	  return XML_ERROR_UNDEFINED_ENTITY;
	}
	if (entity->open)
	  return XML_ERROR_RECURSIVE_ENTITY_REF;
	if (entity->textPtr) {
	  enum XML_Error result;
	  result = processInternalParamEntity(parser, entity);
	  if (result != XML_ERROR_NONE)
	    return result;
	  break;
	}
	if (role == XML_ROLE_INNER_PARAM_ENTITY_REF)
	  return XML_ERROR_PARAM_ENTITY_REF;
	if (externalEntityRefHandler) {
	  dtd.complete = 0;
	  entity->open = 1;
	  if (!externalEntityRefHandler(externalEntityRefHandlerArg,
					0,
					entity->base,
					entity->systemId,
					entity->publicId)) {
	    entity->open = 0;
	    return XML_ERROR_EXTERNAL_ENTITY_HANDLING;
	  }
	  entity->open = 0;
	  if (dtd.complete)
	    break;
	}
      }
#endif /* XML_DTD */
      if (!dtd.standalone
	  && notStandaloneHandler
	  && !notStandaloneHandler(handlerArg))
	return XML_ERROR_NOT_STANDALONE;
      dtd.complete = 0;
      if (defaultHandler)
	reportDefault(parser, enc, s, next);
      break;

      /* Element declaration stuff */

    case XML_ROLE_ELEMENT_NAME:
      if (elementDeclHandler) {
	declElementType = getElementType(parser, enc, s, next);
	if (! declElementType)
	  return XML_ERROR_NO_MEMORY;
	dtd.scaffLevel = 0;
	dtd.scaffCount = 0;
	dtd.in_eldecl = 1;
      }
      break;

    case XML_ROLE_CONTENT_ANY:
    case XML_ROLE_CONTENT_EMPTY:
      if (dtd.in_eldecl) {
	if (elementDeclHandler) {
	  XML_Content * content = (XML_Content *) MALLOC(sizeof(XML_Content));
	  if (! content)
	    return XML_ERROR_NO_MEMORY;
	  content->quant = XML_CQUANT_NONE;
	  content->name = 0;
	  content->numchildren = 0;
	  content->children = 0;
	  content->type = ((role == XML_ROLE_CONTENT_ANY) ?
			   XML_CTYPE_ANY :
			   XML_CTYPE_EMPTY);
	  *eventEndPP = s;
	  elementDeclHandler(handlerArg, declElementType->name, content);
	}
	dtd.in_eldecl = 0;
      }
      break;
      
    case XML_ROLE_CONTENT_PCDATA:
      if (dtd.in_eldecl) {
	dtd.scaffold[dtd.scaffIndex[dtd.scaffLevel - 1]].type = XML_CTYPE_MIXED;
      }
      break;

    case XML_ROLE_CONTENT_ELEMENT:
      quant = XML_CQUANT_NONE;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_OPT:
      quant = XML_CQUANT_OPT;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_REP:
      quant = XML_CQUANT_REP;
      goto elementContent;
    case XML_ROLE_CONTENT_ELEMENT_PLUS:
      quant = XML_CQUANT_PLUS;
    elementContent:
      if (dtd.in_eldecl)
	{
	  ELEMENT_TYPE *el;
	  const char *nxt = quant == XML_CQUANT_NONE ? next : next - 1;
	  int myindex = nextScaffoldPart(parser);
	  if (myindex < 0)
	    return XML_ERROR_NO_MEMORY;
	  dtd.scaffold[myindex].type = XML_CTYPE_NAME;
	  dtd.scaffold[myindex].quant = quant;
	  el = getElementType(parser, enc, s, nxt);
	  if (! el)
	    return XML_ERROR_NO_MEMORY;
	  dtd.scaffold[myindex].name = el->name;
	  dtd.contentStringLen +=  nxt - s + 1;
	}
      break;

    case XML_ROLE_GROUP_CLOSE:
      quant = XML_CQUANT_NONE;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_OPT:
      quant = XML_CQUANT_OPT;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_REP:
      quant = XML_CQUANT_REP;
      goto closeGroup;
    case XML_ROLE_GROUP_CLOSE_PLUS:
      quant = XML_CQUANT_PLUS;
    closeGroup:
      if (dtd.in_eldecl) {
	dtd.scaffLevel--;
	dtd.scaffold[dtd.scaffIndex[dtd.scaffLevel]].quant = quant;
	if (dtd.scaffLevel == 0) {
	  if (elementDeclHandler) {
	    XML_Content *model = build_model(parser);
	    if (! model)
	      return XML_ERROR_NO_MEMORY;
	    *eventEndPP = s;
	    elementDeclHandler(handlerArg, declElementType->name, model);
	  }
	  dtd.in_eldecl = 0;
	  dtd.contentStringLen = 0;
	}
      }
      break;
      /* End element declaration stuff */

    case XML_ROLE_NONE:
      switch (tok) {
      case XML_TOK_PI:
	if (!reportProcessingInstruction(parser, enc, s, next))
	  return XML_ERROR_NO_MEMORY;
	break;
      case XML_TOK_COMMENT:
	if (!reportComment(parser, enc, s, next))
	  return XML_ERROR_NO_MEMORY;
	break;
      }
      break;
    }
    if (defaultHandler) {
      switch (tok) {
      case XML_TOK_PI:
      case XML_TOK_COMMENT:
      case XML_TOK_BOM:
      case XML_TOK_XML_DECL:
#ifdef XML_DTD
      case XML_TOK_IGNORE_SECT:
#endif /* XML_DTD */
      case XML_TOK_PARAM_ENTITY_REF:
	break;
      default:
#ifdef XML_DTD
	if (role != XML_ROLE_IGNORE_SECT)
#endif /* XML_DTD */
	  reportDefault(parser, enc, s, next);
      }
    }
    s = next;
    tok = XmlPrologTok(enc, s, end, &next);
  }
  /* not reached */
}