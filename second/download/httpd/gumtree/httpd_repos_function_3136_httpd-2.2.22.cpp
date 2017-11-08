enum XML_Status XMLCALL
XML_ParseBuffer(XML_Parser parser, int len, int isFinal)
{
  const char *start = bufferPtr;
  positionPtr = start;
  bufferEnd += len;
  parseEndByteIndex += len;
  errorCode = processor(parser, start, parseEndPtr = bufferEnd,
                        isFinal ? (const char **)NULL : &bufferPtr);
  if (errorCode == XML_ERROR_NONE) {
    if (!isFinal) {
      XmlUpdatePosition(encoding, positionPtr, bufferPtr, &position);
      positionPtr = bufferPtr;
    }
    return XML_STATUS_OK;
  }
  else {
    eventEndPtr = eventPtr;
    processor = errorProcessor;
    return XML_STATUS_ERROR;
  }
}