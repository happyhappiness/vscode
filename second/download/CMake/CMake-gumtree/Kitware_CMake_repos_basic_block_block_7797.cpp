{
    case XML_TOK_CDATA_SECT_CLOSE:
      if (endCdataSectionHandler)
        endCdataSectionHandler(handlerArg);
#if 0
      /* see comment under XML_TOK_CDATA_SECT_OPEN */
      else if (characterDataHandler)
        characterDataHandler(handlerArg, dataBuf, 0);
#endif
      else if (defaultHandler)
        reportDefault(parser, enc, s, next);
      *startPtr = next;
      *nextPtr = next;
      if (ps_parsing == XML_FINISHED)
        return XML_ERROR_ABORTED;
      else
        return XML_ERROR_NONE;
    case XML_TOK_DATA_NEWLINE:
      if (characterDataHandler) {
        XML_Char c = 0xA;
        characterDataHandler(handlerArg, &c, 1);
      }
      else if (defaultHandler)
        reportDefault(parser, enc, s, next);
      break;
    case XML_TOK_DATA_CHARS:
      {
        XML_CharacterDataHandler charDataHandler = characterDataHandler;
        if (charDataHandler) {
          if (MUST_CONVERT(enc, s)) {
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
                            (int)((XML_Char *)next - (XML_Char *)s));
        }
        else if (defaultHandler)
          reportDefault(parser, enc, s, next);
      }
      break;
    case XML_TOK_INVALID:
      *eventPP = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    case XML_TOK_PARTIAL:
    case XML_TOK_NONE:
      if (haveMore) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_CDATA_SECTION;
    default:
      *eventPP = next;
      return XML_ERROR_UNEXPECTED_STATE;
    }