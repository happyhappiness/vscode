static XML_Content *
build_model (XML_Parser parser)
{
  XML_Content *ret;
  XML_Content *cpos;
  char * str;
  int allocsize = dtd.scaffCount * sizeof(XML_Content) + dtd.contentStringLen;
  
  ret = MALLOC(allocsize);
  if (! ret)
    return 0;

  str =  (char *) (&ret[dtd.scaffCount]);
  cpos = &ret[1];

  build_node(parser, 0, ret, &cpos, &str);
  return ret;
}