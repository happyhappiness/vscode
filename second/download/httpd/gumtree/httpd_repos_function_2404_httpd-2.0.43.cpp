void XML_ParserFree(XML_Parser parser)
{
  for (;;) {
    TAG *p;
    if (tagStack == 0) {
      if (freeTagList == 0)
	break;
      tagStack = freeTagList;
      freeTagList = 0;
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
  if (parentParser) {
    if (hadExternalDoctype)
      dtd.complete = 0;
    dtdSwap(&dtd, &((Parser *)parentParser)->m_dtd);
  }
#endif /* XML_DTD */
  dtdDestroy(&dtd, parser);
  FREE((void *)atts);
  if (groupConnector)
    FREE(groupConnector);
  if (buffer)
    FREE(buffer);
  FREE(dataBuf);
  if (unknownEncodingMem)
    FREE(unknownEncodingMem);
  if (unknownEncodingRelease)
    unknownEncodingRelease(unknownEncodingData);
  FREE(parser);
}