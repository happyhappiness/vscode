{
          ICHAR *dataPtr = (ICHAR *)dataBuf;
          XmlConvert(enc, &s, end, &dataPtr, (ICHAR *)dataBufEnd);
          characterDataHandler(handlerArg, dataBuf,
                               (int)(dataPtr - (ICHAR *)dataBuf));
        }