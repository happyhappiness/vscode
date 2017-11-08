struct mallinfo dlmallinfo(void) {
  return internal_mallinfo(gm);
}