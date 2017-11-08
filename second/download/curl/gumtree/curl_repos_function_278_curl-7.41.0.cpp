static char *
buffer_threaded(localkey_t key, long size)

{
  buffer_t * bufs;

  /* Get the buffer for the given local key in the current thread, and
     make sure it is at least `size'-byte long. Set `size' to < 0 to get
     its address only. */

  bufs = (buffer_t *) pthread_getspecific(thdkey);

  if(!bufs) {
    if(size < 0)
      return (char *) NULL;             /* No buffer yet. */

    /* Allocate buffer descriptors for the current thread. */

    if(!(bufs = calloc((size_t) LK_LAST, sizeof *bufs)))
      return (char *) NULL;

    if(pthread_setspecific(thdkey, (void *) bufs)) {
      free(bufs);
      return (char *) NULL;
      }
    }

  return get_buffer(bufs + key, size);
}