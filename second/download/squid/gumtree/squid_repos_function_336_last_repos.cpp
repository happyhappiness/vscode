size_t
lt_strlcat(char *dst, const char *src, const size_t dstsize)
{
  size_t length;
  char *p;
  const char *q;

  assert(dst != NULL);
  assert(src != (const char *) NULL);
  assert(dstsize >= 1);

  length=strlen(dst);

  /*
    Copy remaining characters from src while constraining length to
    size - 1.
  */
  for ( p = dst + length, q = src;
        (*q != 0) && (length < dstsize - 1);
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