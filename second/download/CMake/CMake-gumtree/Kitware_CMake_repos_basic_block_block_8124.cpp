(context = s + 1;
           *context != CONTEXT_SEP && *context != XML_T('\0');
           context++)
        if (!poolAppendChar(&tempPool, *context))
          return XML_FALSE;