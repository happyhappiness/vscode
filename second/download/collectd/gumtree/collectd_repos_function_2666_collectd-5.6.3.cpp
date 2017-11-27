static void my_log(int severity, const char *msg, user_data_t *ud) {
  printf("LOG: %i - %s\n", severity, msg);
  return;
}