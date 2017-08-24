(s = e->name; *s; s++)
      if (!poolAppendChar(&tempPool, *s))
        return 0;