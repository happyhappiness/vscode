static int conn_read_file(const char *file) {
  FILE *fh;
  char buffer[1024];

  fh = fopen(file, "r");
  if (fh == NULL)
    return (-1);

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    conn_handle_line(buffer);
  } /* while (fgets) */

  fclose(fh);

  return (0);
}