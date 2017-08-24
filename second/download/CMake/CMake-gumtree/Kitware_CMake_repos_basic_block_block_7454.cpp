{
    FREE(atts);
#ifdef XML_ATTR_INFO
    FREE(attInfo);
#endif
    FREE(parser);
    return NULL;
  }