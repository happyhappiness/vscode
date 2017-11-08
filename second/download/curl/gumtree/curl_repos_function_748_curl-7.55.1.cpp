static size_t read_callback(char *buf, size_t size, size_t n, void *ctx) {
  if(wrote || size * n == 0) {
    return 0;
  }
  wrote = 1;
  buf[0] = 'a';
  return 1;
}