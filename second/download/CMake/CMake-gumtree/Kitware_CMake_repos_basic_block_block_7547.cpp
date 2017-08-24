(ps_parsing) {
    case XML_SUSPENDED:
      result = XML_STATUS_SUSPENDED;
      break;
    case XML_INITIALIZED:
    case XML_PARSING:
      if (isFinal) {
        ps_parsing = XML_FINISHED;
        return result;
      }
    default: ;  /* should not happen */
    }