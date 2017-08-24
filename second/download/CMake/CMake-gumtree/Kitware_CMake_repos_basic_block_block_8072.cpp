{
      ICHAR *dataPtr = (ICHAR *)dataBuf;
      convert_res = XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)dataBufEnd);
      *eventEndPP = s;
      defaultHandler(handlerArg, dataBuf, (int)(dataPtr - (ICHAR *)dataBuf));
      *eventPP = s;
    }