static int alloc_addbyter(int output, FILE *data)
{
  struct asprintf *infop=(struct asprintf *)data;
  unsigned char outc = (unsigned char)output;

  if(!infop->buffer) {
    infop->buffer=(char *)malloc(32);
    if(!infop->buffer) {
      infop->fail = TRUE;
      return -1; /* fail */
    }
    infop->alloc = 32;
    infop->len =0;
  }
  else if(infop->len+1 >= infop->alloc) {
    char *newptr;

    newptr = (char *)realloc(infop->buffer, infop->alloc*2);

    if(!newptr) {
      infop->fail = TRUE;
      return -1;
    }
    infop->buffer = newptr;
    infop->alloc *= 2;
  }

  infop->buffer[ infop->len ] = outc;

  infop->len++;

  return outc; /* fputc() returns like this on success */
}