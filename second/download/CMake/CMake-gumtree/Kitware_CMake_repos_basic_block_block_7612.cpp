{
  enum XML_Error result = doContent(parser, 1, encoding, start, end,
                                    endPtr, (XML_Bool)!ps_finalBuffer);
  if (result == XML_ERROR_NONE) {
    if (!storeRawNames(parser))
      return XML_ERROR_NO_MEMORY;
  }
  return result;
}