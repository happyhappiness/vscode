{
    ps_finalBuffer = (XML_Bool)isFinal;
    if (!isFinal)
      return XML_STATUS_OK;
    positionPtr = bufferPtr;
    parseEndPtr = bufferEnd;

    /* If data are left over from last buffer, and we now know that these
       data are the final chunk of input, then we have to check them again
       to detect errors based on that fact.
    */
    errorCode = processor(parser, bufferPtr, parseEndPtr, &bufferPtr);

    if (errorCode == XML_ERROR_NONE) {
      switch (ps_parsing) {
      case XML_SUSPENDED:
        XmlUpdatePosition(encoding, positionPtr, bufferPtr, &position);
        positionPtr = bufferPtr;
        return XML_STATUS_SUSPENDED;
      case XML_INITIALIZED:
      case XML_PARSING:
        ps_parsing = XML_FINISHED;
        /* fall through */
      default:
        return XML_STATUS_OK;
      }
    }
    eventEndPtr = eventPtr;
    processor = errorProcessor;
    return XML_STATUS_ERROR;
  }