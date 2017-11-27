size_t
lt_strlcpy(char *dst, const char *src, const size_t dstsize)
{
  size_t length=0;
  char *p;
  const char *q;

  assert(dst != NULL);
  assert(src != (const char *) NULL);
  assert(dstsize >= 1);

  /*
    Copy src to dst within bounds of size-1.
  */
  for ( p=dst, q=src, length=0 ;
        (*q != 0) && (length < dstsize-1) ;
        length++, p++, q++ )
    *p = *q;

  dst[length]='\0';

  /*
    Add remaining length of src to length.
  */
  while (*q++)
    length++;

  return length;
}