static size_t write_callback(char *ptr, size_t size, size_t n, void *ctx) {
  return size * n;
}