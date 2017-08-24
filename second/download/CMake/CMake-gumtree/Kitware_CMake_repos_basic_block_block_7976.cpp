{
        enum XML_Error result = processXmlDecl(parser, 1, s, next);
        if (result != XML_ERROR_NONE)
          return result;
        enc = encoding;
        handleDefault = XML_FALSE;
      }