static char *
buffer_unthreaded(localkey_t key, long size)

{
  return get_buffer(locbufs + key, size);
}