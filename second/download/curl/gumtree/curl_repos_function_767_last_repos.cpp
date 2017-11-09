static char *printable(char *inbuf, size_t inlength)
{
  char *outbuf;
  char *newbuf;
  size_t newsize;
  size_t outsize;
  size_t outincr = 0;
  size_t i, o = 0;

#define HEX_FMT_STR  "[0x%02X]"
#define HEX_STR_LEN  6
#define NOTHING_STR  "[NOTHING]"
#define NOTHING_LEN  9

  if(!inlength)
    inlength = strlen(inbuf);

  if(inlength) {
    outincr = ((inlength/2) < (HEX_STR_LEN + 1)) ?
      HEX_STR_LEN + 1 : inlength/2;
    outsize = inlength + outincr;
  }
  else
    outsize = NOTHING_LEN + 1;

  outbuf = malloc(outsize);
  if(!outbuf)
    return NULL;

  if(!inlength) {
    snprintf(&outbuf[0], outsize, "%s", NOTHING_STR);
    return outbuf;
  }

  for(i = 0; i<inlength; i++) {

    if(o > outsize - (HEX_STR_LEN + 1)) {
      newsize = outsize + outincr;
      newbuf = realloc(outbuf, newsize);
      if(!newbuf) {
        free(outbuf);
        return NULL;
      }
      outbuf = newbuf;
      outsize = newsize;
    }

    if((inbuf[i] > 0x20) && (inbuf[i] < 0x7F)) {
      outbuf[o] = inbuf[i];
      o++;
    }
    else {
      snprintf(&outbuf[o], outsize - o, HEX_FMT_STR, inbuf[i]);
      o += HEX_STR_LEN;
    }

  }
  outbuf[o] = '\0';

  return outbuf;
}