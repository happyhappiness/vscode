{
      enum XML_Error result;
      result = processXmlDecl(parser, 0, start, next);
      if (result != XML_ERROR_NONE)
        return result;
      switch (ps_parsing) {
      case XML_SUSPENDED:
        *nextPtr = next;
        return XML_ERROR_NONE;
      case XML_FINISHED:
        return XML_ERROR_ABORTED;
      default:
        *nextPtr = next;
      }
      /* stop scanning for text declaration - we found one */
      processor = entityValueProcessor;
      return entityValueProcessor(parser, next, end, nextPtr);
    }