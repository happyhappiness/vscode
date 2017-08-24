{
    /* only do this if we haven't reached max length yet */
    infop->buffer[0] = outc; /* store */
    infop->buffer++; /* increase pointer */
    infop->length++; /* we are now one byte larger */
    return outc;     /* fputc() returns like this on success */
  }