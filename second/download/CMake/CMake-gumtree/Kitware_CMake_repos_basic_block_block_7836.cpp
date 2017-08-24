{
  enum XML_Error result = initializeEncoding(parser);
  if (result != XML_ERROR_NONE)
    return result;
  processor = prologProcessor;
  return prologProcessor(parser, s, end, nextPtr);
}