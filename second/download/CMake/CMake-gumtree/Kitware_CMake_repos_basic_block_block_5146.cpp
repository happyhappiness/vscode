{
      /* we had data in the "cache", copy that instead of doing an actual
       * read
       *
       * pp->cache_size is cast to ssize_t here.  This should be safe, because
       * it would have been populated with something of size int to begin
       * with, even though its datatype may be larger than an int.
       */
      DEBUGASSERT((ptr+pp->cache_size) <= (buf+data->set.buffer_size+1));
      memcpy(ptr, pp->cache, pp->cache_size);
      gotbytes = (ssize_t)pp->cache_size;
      free(pp->cache);    /* free the cache */
      pp->cache = NULL;   /* clear the pointer */
      pp->cache_size = 0; /* zero the size just in case */
    }