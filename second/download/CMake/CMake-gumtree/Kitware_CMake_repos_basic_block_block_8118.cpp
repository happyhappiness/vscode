(i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, dtd->defaultPrefix.binding->uri[i]))
        return NULL;