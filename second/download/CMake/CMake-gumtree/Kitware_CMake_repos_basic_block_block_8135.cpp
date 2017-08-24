(*s == XML_T(ASCII_EQUALS)) {
      PREFIX *prefix;
      if (poolLength(&tempPool) == 0)
        prefix = &dtd->defaultPrefix;
      else {
        if (!poolAppendChar(&tempPool, XML_T('\0')))
          return XML_FALSE;
        prefix = (PREFIX *)lookup(parser, &dtd->prefixes, poolStart(&tempPool),
                                  sizeof(PREFIX));
        if (!prefix)
          return XML_FALSE;
        if (prefix->name == poolStart(&tempPool)) {
          prefix->name = poolCopyString(&dtd->pool, prefix->name);
          if (!prefix->name)
            return XML_FALSE;
        }
        poolDiscard(&tempPool);
      }
      for (context = s + 1;
           *context != CONTEXT_SEP && *context != XML_T('\0');
           context++)
        if (!poolAppendChar(&tempPool, *context))
          return XML_FALSE;
      if (!poolAppendChar(&tempPool, XML_T('\0')))
        return XML_FALSE;
      if (addBinding(parser, prefix, NULL, poolStart(&tempPool),
                     &inheritedBindings) != XML_ERROR_NONE)
        return XML_FALSE;
      poolDiscard(&tempPool);
      if (*context != XML_T('\0'))
        ++context;
      s = context;
    }