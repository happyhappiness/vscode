{
    char *newptr = NULL;
    size_t newsize = infop->alloc*2;

    /* detect wrap-around or other overflow problems */
    if(newsize > infop->alloc)
      newptr = realloc(infop->buffer, newsize);

    if(!newptr) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->buffer = newptr;
    infop->alloc = newsize;
  }