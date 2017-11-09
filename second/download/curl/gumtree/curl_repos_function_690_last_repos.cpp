static int readline(char **buffer, size_t *bufsize, FILE *stream)
{
  size_t offset = 0;
  size_t length;
  char *newptr;

  if(!*buffer) {
    *buffer = malloc(128);
    if(!*buffer)
      return GPE_OUT_OF_MEMORY;
    *bufsize = 128;
  }

  for(;;) {
    int bytestoread = curlx_uztosi(*bufsize - offset);

    if(!fgets(*buffer + offset, bytestoread, stream))
      return (offset != 0) ? GPE_OK : GPE_END_OF_FILE;

    length = offset + strlen(*buffer + offset);
    if(*(*buffer + length - 1) == '\n')
      break;
    offset = length;
    if(length < *bufsize - 1)
      continue;

    newptr = realloc(*buffer, *bufsize * 2);
    if(!newptr)
      return GPE_OUT_OF_MEMORY;
    *buffer = newptr;
    *bufsize *= 2;
  }

  return GPE_OK;
}