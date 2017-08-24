(parentParser == NULL && !startParsing(parser)) {
      errorCode = XML_ERROR_NO_MEMORY;
      return XML_STATUS_ERROR;
    }