{
      memcpy(buff, s, len);
      return XML_ParseBuffer(parser, len, isFinal);
    }