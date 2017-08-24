      if(source)
        fprintf(stderr, "LIMIT %s:%d %s reached memlimit\n",
                source, line, func);
      errno = ENOMEM;
      return TRUE; /* RETURN ERROR! */
    }
    else
