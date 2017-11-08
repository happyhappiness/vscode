static void fail(const char *why) {
  perror(why);
  exit(1);
}