{
    queue_size = queued_fds->size + 8;
    queued_fds = uv__realloc(queued_fds,
                             (queue_size - 1) * sizeof(*queued_fds->fds) +
                              sizeof(*queued_fds));

    /*
     * Allocation failure, report back.
     * NOTE: if it is fatal - sockets will be closed in uv__stream_close
     */
    if (queued_fds == NULL)
      return -ENOMEM;
    queued_fds->size = queue_size;
    stream->queued_fds = queued_fds;
  }