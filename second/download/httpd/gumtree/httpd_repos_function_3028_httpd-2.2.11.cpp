int XML_Parse(XML_Parser parser, const char *s, int len, int isFinal)
{
  if (len == 0) {
    if (!isFinal)
      return 1;
    positionPtr = bufferPtr;
    errorCode = processor(parser, bufferPtr, parseEndPtr = bufferEnd, 0);
    if (errorCode == XML_ERROR_NONE)
      return 1;
    eventEndPtr = eventPtr;
    processor = errorProcessor;
    return 0;
  }
#ifndef XML_CONTEXT_BYTES
  else if (bufferPtr == bufferEnd) {
    const char *end;
    int nLeftOver;
    parseEndByteIndex += len;
    positionPtr = s;
    if (isFinal) {
      errorCode = processor(parser, s, parseEndPtr = s + len, 0);
      if (errorCode == XML_ERROR_NONE)
	return 1;
      eventEndPtr = eventPtr;
      processor = errorProcessor;
      return 0;
    }
    errorCode = processor(parser, s, parseEndPtr = s + len, &end);
    if (errorCode != XML_ERROR_NONE) {
      eventEndPtr = eventPtr;
      processor = errorProcessor;
      return 0;
    }
    XmlUpdatePosition(encoding, positionPtr, end, &position);
    nLeftOver = s + len - end;
    if (nLeftOver) {
      if (buffer == 0 || nLeftOver > bufferLim - buffer) {
	/* FIXME avoid integer overflow */
	buffer = buffer == 0 ? MALLOC(len * 2) : REALLOC(buffer, len * 2);
	/* FIXME storage leak if realloc fails */
	if (!buffer) {
	  errorCode = XML_ERROR_NO_MEMORY;
	  eventPtr = eventEndPtr = 0;
	  processor = errorProcessor;
	  return 0;
	}
	bufferLim = buffer + len * 2;
      }
      memcpy(buffer, end, nLeftOver);
      bufferPtr = buffer;
      bufferEnd = buffer + nLeftOver;
    }
    return 1;
  }
#endif  /* not defined XML_CONTEXT_BYTES */
  else {
    memcpy(XML_GetBuffer(parser, len), s, len);
    return XML_ParseBuffer(parser, len, isFinal);
  }
}