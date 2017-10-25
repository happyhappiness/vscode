static int addbyter(int output, FILE *data)
{
  struct nsprintf *infop=(struct nsprintf *)data;
 
  if(infop->length < infop->max) {
    /* only do this if we haven't reached max length yet */
    if (isprint(output) || isspace(output))
      {
	infop->buffer[0] = (char)output; /* store */
	infop->buffer++; /* increase pointer */
	infop->length++; /* we are now one byte larger */
      }
    else
      {
	return StoreNonPrintable(output, infop);
      }
    return output; /* fputc() returns like this on success */
  }
  return -1;
}