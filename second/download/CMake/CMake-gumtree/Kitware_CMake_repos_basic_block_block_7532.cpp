{
    const char *end;
    int nLeftOver;
    enum XML_Status result;
    /* Detect overflow (a+b > MAX <==> b > MAX-a) */
    if (len > ((XML_Size)-1) / 2 - parseEndByteIndex) {
       errorCode = XML_ERROR_NO_MEMORY;
       eventPtr = eventEndPtr = NULL;
       processor = errorProcessor;
       return XML_STATUS_ERROR;
    }
    parseEndByteIndex += len;
    positionPtr = s;
    ps_finalBuffer = (XML_Bool)isFinal;

    errorCode = processor(parser, s, parseEndPtr = s + len, &end);

    if (errorCode != XML_ERROR_NONE) {
      eventEndPtr = eventPtr;
      processor = errorProcessor;
      return XML_STATUS_ERROR;
    }
    else {
      switch (ps_parsing) {
      case XML_SUSPENDED:
        result = XML_STATUS_SUSPENDED;
        break;
      case XML_INITIALIZED:
      case XML_PARSING:
        if (isFinal) {
          ps_parsing = XML_FINISHED;
          return XML_STATUS_OK;
        }
      /* fall through */
      default:
        result = XML_STATUS_OK;
      }
    }

    XmlUpdatePosition(encoding, positionPtr, end, &position);
    nLeftOver = s + len - end;
    if (nLeftOver) {
      if (buffer == NULL || nLeftOver > bufferLim - buffer) {
        /* avoid _signed_ integer overflow */
        char *temp = NULL;
        const int bytesToAllocate = (int)((unsigned)len * 2U);
        if (bytesToAllocate > 0) {
          temp = (buffer == NULL
                ? (char *)MALLOC(bytesToAllocate)
                : (char *)REALLOC(buffer, bytesToAllocate));
        }
        if (temp == NULL) {
          errorCode = XML_ERROR_NO_MEMORY;
          eventPtr = eventEndPtr = NULL;
          processor = errorProcessor;
          return XML_STATUS_ERROR;
        }
        buffer = temp;
        bufferLim = buffer + bytesToAllocate;
      }
      memcpy(buffer, end, nLeftOver);
    }
    bufferPtr = buffer;
    bufferEnd = buffer + nLeftOver;
    positionPtr = bufferPtr;
    parseEndPtr = bufferEnd;
    eventPtr = bufferPtr;
    eventEndPtr = bufferPtr;
    return result;
  }