static int StoreNonPrintable(int output, struct nsprintf *infop)
{
  /* If the character isn't printable then we convert it */
  char work[64], *w;
  int num = output;

  w = &work[sizeof(work)];
  *(--w) = (char)0;
  for(; num > 0; num /= 10) {
    *(--w) = lower_digits[num % 10];
  }
  if (infop->length + strlen(w) + 1 < infop->max)
    {
      infop->buffer[0] = '\\';
      infop->buffer++;
      infop->length++;
      for (; *w; w++)
	{
	  infop->buffer[0] = *w;
	  infop->buffer++;
	  infop->length++;
	}
      return output;
    }
  return -1;
}