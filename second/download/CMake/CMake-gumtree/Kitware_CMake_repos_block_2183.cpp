{
  (void)ac;
  (void)av;
  int ret = bar();
  printf("bar = %d\n", ret);
  if (ret == 10) {
    return 0;
  }
  return -1;
}