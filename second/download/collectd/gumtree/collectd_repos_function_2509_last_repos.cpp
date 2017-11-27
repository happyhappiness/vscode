static int buffer_next(buffer_t *b, void *out, size_t n) {
  if (b->len < n) {
    return -1;
  }
  memmove(out, b->data, n);

  b->data += n;
  b->len -= n;

  return 0;
}