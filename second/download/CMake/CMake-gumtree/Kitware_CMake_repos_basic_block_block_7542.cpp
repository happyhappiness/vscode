{
  case XML_SUSPENDED:
    errorCode = XML_ERROR_SUSPENDED;
    return XML_STATUS_ERROR;
  case XML_FINISHED:
    errorCode = XML_ERROR_FINISHED;
    return XML_STATUS_ERROR;
  case XML_INITIALIZED:
    if (parentParser == NULL && !startParsing(parser)) {
      errorCode = XML_ERROR_NO_MEMORY;
      return XML_STATUS_ERROR;
    }
  default:
    ps_parsing = XML_PARSING;
  }