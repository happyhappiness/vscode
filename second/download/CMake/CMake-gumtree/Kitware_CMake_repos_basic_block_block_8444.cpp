{
    case '\"':
      result += "\\\"";
      break;
    case '\\':
      result += "\\\\";
      break;
    case '\b':
      result += "\\b";
      break;
    case '\f':
      result += "\\f";
      break;
    case '\n':
      result += "\\n";
      break;
    case '\r':
      result += "\\r";
      break;
    case '\t':
      result += "\\t";
      break;
    // case '/':
    // Even though \/ is considered a legal escape in JSON, a bare
    // slash is also legal, so I see no reason to escape it.
    // (I hope I am not misunderstanding something.
    // blep notes: actually escaping \/ may be useful in javascript to avoid </
    // sequence.
    // Should add a flag to allow this compatibility mode and prevent this
    // sequence from occurring.
    default:
      if (isControlCharacter(*c)) {
        std::ostringstream oss;
        oss << "\\u" << std::hex << std::uppercase << std::setfill('0')
            << std::setw(4) << static_cast<int>(*c);
        result += oss.str();
      } else {
        result += *c;
      }
      break;
    }