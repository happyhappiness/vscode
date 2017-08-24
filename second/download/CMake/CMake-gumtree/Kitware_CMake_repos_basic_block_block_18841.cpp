{
  loop->cf_state = NULL;

  if (uv__kqueue_init(loop))
    return -errno;

  return 0;
}