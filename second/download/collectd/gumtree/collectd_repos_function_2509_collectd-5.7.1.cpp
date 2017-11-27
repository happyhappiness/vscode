int escape_string(char *buffer, size_t buffer_size) {
  char *temp;
  size_t j;

  /* Check if we need to escape at all first */
  temp = strpbrk(buffer, " \t\"\\");
  if (temp == NULL)
    return (0);

  if (buffer_size < 3)
    return (EINVAL);

  temp = calloc(1, buffer_size);
  if (temp == NULL)
    return (ENOMEM);

  temp[0] = '"';
  j = 1;

  for (size_t i = 0; i < buffer_size; i++) {
    if (buffer[i] == 0) {
      break;
    } else if ((buffer[i] == '"') || (buffer[i] == '\\')) {
      if (j > (buffer_size - 4))
        break;
      temp[j] = '\\';
      temp[j + 1] = buffer[i];
      j += 2;
    } else {
      if (j > (buffer_size - 3))
        break;
      temp[j] = buffer[i];
      j++;
    }
  }

  assert((j + 1) < buffer_size);
  temp[j] = '"';
  temp[j + 1] = 0;

  sstrncpy(buffer, temp, buffer_size);
  sfree(temp);
  return (0);
}