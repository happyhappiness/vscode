void* dlmemalign(size_t alignment, size_t bytes) {
  return internal_memalign(gm, alignment, bytes);
}