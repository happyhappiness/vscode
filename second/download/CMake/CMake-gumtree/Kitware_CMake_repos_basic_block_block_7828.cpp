(xmlDeclHandler) {
    if (encodingName != NULL) {
      storedEncName = poolStoreString(&temp2Pool,
                                      encoding,
                                      encodingName,
                                      encodingName
                                      + XmlNameLength(encoding, encodingName));
      if (!storedEncName)
              return XML_ERROR_NO_MEMORY;
      poolFinish(&temp2Pool);
    }
    if (version) {
      storedversion = poolStoreString(&temp2Pool,
                                      encoding,
                                      version,
                                      versionend - encoding->minBytesPerChar);
      if (!storedversion)
        return XML_ERROR_NO_MEMORY;
    }
    xmlDeclHandler(handlerArg, storedversion, storedEncName, standalone);
  }
  else if (defaultHandler)
    reportDefault(parser, encoding, s, next)