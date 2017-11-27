static int openvpn_strsplit(char *string, char **fields, size_t size) {
  size_t i = 0;
  char *ptr = string;
  char *saveptr = NULL;

  while ((fields[i] = strtok_r(ptr, ",\t", &saveptr)) != NULL) {
    ptr = NULL;
    i++;

    if (i >= size)
      break;
  }

  return i;
}