{  /* we are parsing an external entity */
      processor = externalEntityContentProcessor;
      return externalEntityContentProcessor(parser, start, end, endPtr);
    }