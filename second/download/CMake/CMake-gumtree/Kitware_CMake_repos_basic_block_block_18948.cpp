{
    if (cb != NULL)
      uv__req_unregister(loop, req);
    return -ENOMEM;
  }