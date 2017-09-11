inline void HandleAssertError(const char *msg) {
  fprintf(stderr, "AssertError:%s\n", msg);
  exit(-1);
}