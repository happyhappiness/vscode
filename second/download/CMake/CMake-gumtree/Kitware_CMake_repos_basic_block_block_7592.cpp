(openInternalEntities)
      reportDefault(parser,
                    internalEncoding,
                    openInternalEntities->internalEventPtr,
                    openInternalEntities->internalEventEndPtr);
    else
      reportDefault(parser, encoding, eventPtr, eventEndPtr)