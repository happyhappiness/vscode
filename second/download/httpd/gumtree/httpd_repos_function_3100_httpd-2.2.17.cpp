const char * XMLCALL
XML_GetInputContext(XML_Parser parser, int *offset, int *size)
{
#ifdef XML_CONTEXT_BYTES
  if (eventPtr && buffer) {
    *offset = eventPtr - buffer;
    *size   = bufferEnd - buffer;
    return buffer;
  }
#endif /* defined XML_CONTEXT_BYTES */
  return (char *) 0;
}