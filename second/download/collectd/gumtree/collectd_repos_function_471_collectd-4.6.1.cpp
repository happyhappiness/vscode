static void remove_special (char *buffer, size_t buffer_size) /* {{{ */
{
  size_t i;

  for (i = 0; i < buffer_size; i++)
  {
    if (buffer[i] == 0)
      return;
    if ((!isalnum ((int) buffer[i])) && (buffer[i] != '-'))
      buffer[i] = '_';
  }
}