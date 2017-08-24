(tok == XML_TOK_INSTANCE_START) {
      *nextPtr = next;
      return XML_ERROR_SYNTAX;
    }