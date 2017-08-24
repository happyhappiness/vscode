(!dtdCopy(oldParser, _dtd, oldDtd, &parser->m_mem)
      || !setContext(parser, context)) {
      XML_ParserFree(parser);
      return NULL;
    }