(characterDataHandler) {
        if (MUST_CONVERT(enc, s)) {
          ICHAR *dataPtr = (ICHAR *)dataBuf;
          XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)dataBufEnd);
          characterDataHandler(handlerArg, dataBuf,
                               (int)(dataPtr - (ICHAR *)dataBuf));
        }
        else
          characterDataHandler(handlerArg,
                               (XML_Char *)s,
                               (int)((XML_Char *)end - (XML_Char *)s));
      }
      else if (defaultHandler)
        reportDefault(parser, enc, s, end)