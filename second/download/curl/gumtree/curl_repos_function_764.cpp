ParameterError file2memory(char **bufp, size_t *size, FILE *file)
{
  char *newbuf;
  char *buffer = NULL;
  size_t alloc = 512;
  size_t nused = 0;
  size_t nread;

  if(file) {
    do {
      if(!buffer || (alloc == nused)) {
        /* size_t overflow detection for huge files */
        if(alloc+1 > ((size_t)-1)/2) {
          Curl_safefree(buffer);
          return PARAM_NO_MEM;
        }
        alloc *= 2;
        /* allocate an extra char, reserved space, for null termination */
        if((newbuf = realloc(buffer, alloc+1)) == NULL) {
          Curl_safefree(buffer);
          return PARAM_NO_MEM;
        }
        buffer = newbuf;
      }
      nread = fread(buffer+nused, 1, alloc-nused, file);
      nused += nread;
    } while(nread);
    /* null terminate the buffer in case it's used as a string later */
    buffer[nused] = '\0';
    /* free trailing slack space, if possible */
    if(alloc != nused) {
      if((newbuf = realloc(buffer, nused+1)) == NULL) {
        Curl_safefree(buffer);
        return PARAM_NO_MEM;
      }
      buffer = newbuf;
    }
    /* discard buffer if nothing was read */
    if(!nused) {
      Curl_safefree(buffer); /* no string */
    }
  }
  *size = nused;
  *bufp = buffer;
  return PARAM_OK;
}