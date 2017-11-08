int XML_GetCurrentByteCount(XML_Parser parser)
{
  if (eventEndPtr && eventPtr)
    return eventEndPtr - eventPtr;
  return 0;
}