(newEncoding->minBytesPerChar != encoding->minBytesPerChar) {
        eventPtr = encodingName;
        return XML_ERROR_INCORRECT_ENCODING;
      }