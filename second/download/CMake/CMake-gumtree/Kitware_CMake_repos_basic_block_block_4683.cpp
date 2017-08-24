{
    infop->buffer = malloc(32);
    if(!infop->buffer) {
      infop->fail = 1;
      return -1; /* fail */
    }
    infop->alloc = 32;
    infop->len =0;
  }