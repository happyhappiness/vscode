static int nut_ca_path(const char *value) {
  if (value != NULL && strcmp(value, "") != 0) {
    ca_path = malloc(strlen(value) + 1);
    strncpy(ca_path, value, (strlen(value) + 1));
  } else {
    ca_path = NULL; // Should alread be set to NULL from initialization
  }
  return 0;
}