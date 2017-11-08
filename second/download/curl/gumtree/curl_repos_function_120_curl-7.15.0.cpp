static
char *appendstring(char *string, /* original string */
                   char *buffer, /* to append */
                   size_t *stringlen, /* length of string */
                   size_t *stralloc,  /* allocated size */
                   char base64) /* 1 if base64 encoded */
{
  size_t len = strlen(buffer);
  size_t needed_len = len + *stringlen + 1;
  char *buf64=NULL;

  if(base64) {
    /* decode the given buffer first */
    len = Curl_base64_decode(buffer, (unsigned char**)&buf64); /* updated len */
    buffer = buf64;
    needed_len = len + *stringlen + 1; /* recalculate */
  }

  if(needed_len >= *stralloc) {
    char *newptr;
    size_t newsize = needed_len*2; /* get twice the needed size */

    newptr = realloc(string, newsize);
    if(newptr) {
      string = newptr;
      *stralloc = newsize;
    }
    else {
      if(buf64)
        free(buf64);
      return NULL;
    }
  }
  /* memcpy to support binary blobs */
  memcpy(&string[*stringlen], buffer, len);
  *stringlen += len;
  string[*stringlen]=0;

  if(buf64)
    free(buf64);

  return string;
}