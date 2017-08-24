{
  case XML_SUSPENDED:
    errorCode = XML_ERROR_SUSPENDED;
    return NULL;
  case XML_FINISHED:
    errorCode = XML_ERROR_FINISHED;
    return NULL;
  default: ;
  }