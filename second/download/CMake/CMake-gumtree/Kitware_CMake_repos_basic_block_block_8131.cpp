(poolLength(&tempPool) == 0)
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