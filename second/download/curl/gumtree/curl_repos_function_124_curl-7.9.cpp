static int AllocAndCopy (char **buffer, int buffer_length)
{
  char *src = *buffer;
  int length;
  if (buffer_length)
    length = buffer_length;
  else
    length = strlen(*buffer);
  *buffer = (char*)malloc(length);
  if (!*buffer)
    return 1;
  memcpy(*buffer, src, length);
  return 0;
}