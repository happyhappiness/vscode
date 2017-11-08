int XML_SetEncoding(XML_Parser parser, const XML_Char *encodingName)
{
  if (!encodingName)
    protocolEncodingName = 0;
  else {
    protocolEncodingName = poolCopyString(&tempPool, encodingName);
    if (!protocolEncodingName)
      return 0;
  }
  return 1;
}