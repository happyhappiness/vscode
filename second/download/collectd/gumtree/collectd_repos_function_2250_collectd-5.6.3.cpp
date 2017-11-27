oconfig_item_t *oconfig_parse_file(const char *file) {
  FILE *fh;
  oconfig_item_t *ret;

  c_file = file;

  fh = fopen(file, "r");
  if (fh == NULL) {
    fprintf(stderr, "fopen (%s) failed: %s\n", file, strerror(errno));
    return (NULL);
  }

  ret = oconfig_parse_fh(fh);
  fclose(fh);

  c_file = NULL;

  return (ret);
}