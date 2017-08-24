(errorCode == XML_ERROR_NONE) {
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