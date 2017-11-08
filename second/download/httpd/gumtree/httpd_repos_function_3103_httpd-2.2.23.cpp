void XMLCALL
XML_SetReturnNSTriplet(XML_Parser parser, int do_nst)
{
  /* block after XML_Parse()/XML_ParseBuffer() has been called */
  if (parsing)
    return;
  ns_triplets = do_nst ? XML_TRUE : XML_FALSE;
}