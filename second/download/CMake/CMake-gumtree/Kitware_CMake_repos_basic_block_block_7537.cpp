(errorCode != XML_ERROR_NONE) {
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