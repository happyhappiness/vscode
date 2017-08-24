(i = 0; i < len; i++)
      if (!poolAppendChar(&tempPool, prefix->binding->uri[i]))
        return NULL;