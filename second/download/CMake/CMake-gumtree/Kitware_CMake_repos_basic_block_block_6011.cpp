{
    result = (*p->setup_connection)(conn);

    if(result)
      return result;

    p = conn->handler;              /* May have changed. */
  }