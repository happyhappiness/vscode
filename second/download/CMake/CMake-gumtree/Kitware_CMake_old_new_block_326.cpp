{
      /* if a line like this was already allocated, free the previous one */
      if(conn->allocptr.rangeline)
        free(conn->allocptr.rangeline);
      conn->allocptr.rangeline = aprintf("Range: bytes=%s\r\n",
                                         data->state.range);
    }