int parse_value_file(char const *path, value_t *ret_value, int ds_type) {
  FILE *fh;
  char buffer[256];

  fh = fopen(path, "r");
  if (fh == NULL)
    return (-1);

  if (fgets(buffer, sizeof(buffer), fh) == NULL) {
    fclose(fh);
    return (-1);
  }

  fclose(fh);

  strstripnewline(buffer);

  return parse_value(buffer, ret_value, ds_type);
}