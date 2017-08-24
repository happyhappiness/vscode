{
    /* report partial linebreak - it might be the last token */
    case -XML_TOK_PROLOG_S:
      if (defaultHandler) {
        reportDefault(parser, encoding, s, next);
        if (ps_parsing == XML_FINISHED)
          return XML_ERROR_ABORTED;
      }
      *nextPtr = next;
      return XML_ERROR_NONE;
    case XML_TOK_NONE:
      *nextPtr = s;
      return XML_ERROR_NONE;
    case XML_TOK_PROLOG_S:
      if (defaultHandler)
        reportDefault(parser, encoding, s, next);
      break;
    case XML_TOK_PI:
      if (!reportProcessingInstruction(parser, encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_COMMENT:
      if (!reportComment(parser, encoding, s, next))
        return XML_ERROR_NO_MEMORY;
      break;
    case XML_TOK_INVALID:
      eventPtr = next;
      return XML_ERROR_INVALID_TOKEN;
    case XML_TOK_PARTIAL:
      if (!ps_finalBuffer) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_UNCLOSED_TOKEN;
    case XML_TOK_PARTIAL_CHAR:
      if (!ps_finalBuffer) {
        *nextPtr = s;
        return XML_ERROR_NONE;
      }
      return XML_ERROR_PARTIAL_CHAR;
    default:
      return XML_ERROR_JUNK_AFTER_DOC_ELEMENT;
    }