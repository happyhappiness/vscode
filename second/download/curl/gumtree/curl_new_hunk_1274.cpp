
/* a handle to number lookup, highly ineffective when we do many
   transfers... */
static int hnd2num(CURL *hnd)
{
  int i;
  for(i = 0; i< num_transfers; i++) {
    if(curl_hnd[i] == hnd)
      return i;
  }
  return 0; /* weird, but just a fail-safe */
}

static
void dump(const char *text, int num, unsigned char *ptr, size_t size,
          char nohex)
{
  size_t i;
  size_t c;
  unsigned int width = 0x10;

  if(nohex)
    /* without the hex output, we can fit more on screen */
    width = 0x40;

  fprintf(stderr, "%d %s, %ld bytes (0x%lx)\n",
          num, text, (long)size, (long)size);

  for(i = 0; i<size; i += width) {

    fprintf(stderr, "%4.4lx: ", (long)i);

    if(!nohex) {
      /* hex not disabled, show it */
      for(c = 0; c < width; c++)
        if(i + c < size)
          fprintf(stderr, "%02x ", ptr[i + c]);
        else
          fputs("   ", stderr);
    }

    for(c = 0; (c < width) && (i + c < size); c++) {
      /* check for 0D0A; if found, skip past and start a new line of output */
      if(nohex && (i + c + 1 < size) && ptr[i + c] == 0x0D &&
         ptr[i + c + 1] == 0x0A) {
        i += (c + 2 - width);
        break;
      }
      fprintf(stderr, "%c",
              (ptr[i + c] >= 0x20) && (ptr[i + c]<0x80)?ptr[i + c]:'.');
      /* check again for 0D0A, to avoid an extra \n if it's at width */
      if(nohex && (i + c + 2 < size) && ptr[i + c + 1] == 0x0D &&
         ptr[i + c + 2] == 0x0A) {
        i += (c + 3 - width);
        break;
      }
    }
    fputc('\n', stderr); /* newline */
  }
}
