static int addbyter(int output, FILE *data)
{
  struct nsprintf *infop=(struct nsprintf *)data;
 
  if(infop->length < infop->max) {
    /* only do this if we haven't reached max length yet */
    infop->buffer[0] = (char)output; /* store */
    infop->buffer++; /* increase pointer */
    infop->length++; /* we are now one byte larger */
    return output; /* fputc() returns like this on success */
  }
  return -1;
}