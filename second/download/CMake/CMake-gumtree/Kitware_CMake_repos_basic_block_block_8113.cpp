(s = prefix->name; *s; s++)
      if (!poolAppendChar(&tempPool, *s))
        return NULL;