static char *memdup(const char *src, size_t buffer_length)
{
  size_t length;
  bool add = FALSE;
  char *buffer;

  if (buffer_length)
    length = buffer_length;
  else {
    length = strlen(src);
    add = TRUE;
  }
  buffer = (char*)malloc(length+add);
  if (!buffer)
    return NULL; /* fail */

  memcpy(buffer, src, length);

  /* if length unknown do null termination */
  if (add)
    buffer[length] = '\0';

  return buffer;
}