ssize_t read_file_contents(const char *filename, char *buf, size_t bufsize) {
  FILE *fh;
  ssize_t ret;

  fh = fopen(filename, "r");
  if (fh == NULL)
    return (-1);

  ret = (ssize_t)fread(buf, 1, bufsize, fh);
  if ((ret == 0) && (ferror(fh) != 0)) {
    ERROR("read_file_contents: Reading file \"%s\" failed.", filename);
    ret = -1;
  }

  fclose(fh);
  return (ret);
}