      if(source)
        fprintf(stderr, "LIMIT %s:%d %s reached memlimit\n",
                source, line, func);
      return TRUE; /* RETURN ERROR! */
    }
    else
