(unknownEncodingHandler(unknownEncodingHandlerData, encodingName,
                               &info)) {
      ENCODING *enc;
      unknownEncodingMem = MALLOC(XmlSizeOfUnknownEncoding());
      if (!unknownEncodingMem) {
        if (info.release)
          info.release(info.data);
        return XML_ERROR_NO_MEMORY;
      }
      enc = (ns
             ? XmlInitUnknownEncodingNS
             : XmlInitUnknownEncoding)(unknownEncodingMem,
                                       info.map,
                                       info.convert,
                                       info.data);
      if (enc) {
        unknownEncodingData = info.data;
        unknownEncodingRelease = info.release;
        encoding = enc;
        return XML_ERROR_NONE;
      }
    }