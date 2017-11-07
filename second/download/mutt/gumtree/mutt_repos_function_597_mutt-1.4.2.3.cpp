static int read_material (size_t material, size_t * used, FILE * fp)
{
  if (*used + material >= plen)
  {
    unsigned char *p;
    size_t nplen;

    nplen = *used + material + CHUNKSIZE;

    if (!(p = realloc (pbuf, nplen)))	/* __MEM_CHECKED__ */
    {
      perror ("realloc");
      return -1;
    }
    plen = nplen;
    pbuf = p;
  }

  if (fread (pbuf + *used, 1, material, fp) < material)
  {
    perror ("fread");
    return -1;
  }

  *used += material;
  return 0;
}