static int AllocAndCopy (char **buffer, int buffer_length)
{
  const char *src = *buffer;
  int length, add = 0;
  if (buffer_length)
    length = buffer_length;
  else {
    length = strlen(*buffer);
    add = 1;
  }
  *buffer = (char*)malloc(length+add);
  if (!*buffer)
    return 1;
  memcpy(*buffer, src, length);
  /* if length unknown do null termination */
  if (add)
    (*buffer)[length] = '\0';
  return 0;
}