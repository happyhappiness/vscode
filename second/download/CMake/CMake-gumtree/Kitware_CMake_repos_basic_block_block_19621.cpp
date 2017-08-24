{
    queue_size = 8;
    queued_fds = uv__malloc((queue_size - 1) * sizeof(*queued_fds->fds) +
                            sizeof(*queued_fds));
    if (queued_fds == NULL)
      return -ENOMEM;
    queued_fds->size = queue_size;
    queued_fds->offset = 0;
    stream->queued_fds = queued_fds;

    /* Grow */
  }