void XMLCALL
XML_ParserFree(XML_Parser parser)
{
  for (;;) {
    TAG *p;
    if (tagStack == NULL) {
      if (freeTagList == NULL)
        break;
      tagStack = freeTagList;
      freeTagList = NULL;
    }
    p = tagStack;
    tagStack = tagStack->parent;
    FREE(p->buf);
    destroyBindings(p->bindings, parser);
    FREE(p);
  }
  destroyBindings(freeBindingList, parser);
  destroyBindings(inheritedBindings, parser);
  poolDestroy(&tempPool);
  poolDestroy(&temp2Pool);
#ifdef XML_DTD
  /* external parameter entity parsers share the DTD structure
     parser->m_dtd with the root parser, so we must not destroy it
  */
  if (!isParamEntity && _dtd)
#else
  if (_dtd)
#endif /* XML_DTD */
    dtdDestroy(_dtd, (XML_Bool)!parentParser, &parser->m_mem);
  FREE((void *)atts);
  FREE(groupConnector);
  FREE(buffer);
  FREE(dataBuf);
  FREE(nsAtts);
  FREE(unknownEncodingMem);
  if (unknownEncodingRelease)
    unknownEncodingRelease(unknownEncodingData);
  FREE(parser);
}