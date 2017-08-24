(MUST_CONVERT(enc, s)) {
            for (;;) {
              ICHAR *dataPtr = (ICHAR *)dataBuf;
              const enum XML_Convert_Result convert_res = XmlConvert(enc, &s, next, &dataPtr, (ICHAR *)dataBufEnd);
              *eventEndPP = next;
              charDataHandler(handlerArg, dataBuf,
                              (int)(dataPtr - (ICHAR *)dataBuf));
              if ((convert_res == XML_CONVERT_COMPLETED) || (convert_res == XML_CONVERT_INPUT_INCOMPLETE))
                break;
              *eventPP = s;
            }
          }
          else
            charDataHandler(handlerArg,
                            (XML_Char *)s,
                            (int)((XML_Char *)next - (XML_Char *)s))