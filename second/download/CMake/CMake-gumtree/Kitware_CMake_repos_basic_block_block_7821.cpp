(protocolEncodingName == NULL) {
    if (newEncoding) {
      if (newEncoding->minBytesPerChar != encoding->minBytesPerChar) {
        eventPtr = encodingName;
        return XML_ERROR_INCORRECT_ENCODING;
      }
      encoding = newEncoding;
    }
    else if (encodingName) {
      enum XML_Error result;
      if (!storedEncName) {
        storedEncName = poolStoreString(
          &temp2Pool, encoding, encodingName,
          encodingName + XmlNameLength(encoding, encodingName));
        if (!storedEncName)
          return XML_ERROR_NO_MEMORY;
      }
      result = handleUnknownEncoding(parser, storedEncName);
      poolClear(&temp2Pool);
      if (result == XML_ERROR_UNKNOWN_ENCODING)
        eventPtr = encodingName;
      return result;
    }
  }