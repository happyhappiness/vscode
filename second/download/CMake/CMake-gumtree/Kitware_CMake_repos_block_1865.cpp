{
  char* env = getenv("DASHBOARD_TEST_FROM_CTEST");
  int oldCtest = 0;
  if (env) {
    if (strcmp(env, "1") == 0) {
      oldCtest = 1;
    }
    printf("DASHBOARD_TEST_FROM_CTEST = %s\n", env);
  }
  printf("%s: This test intentionally fails\n", argv[0]);
  if (oldCtest) {
    printf("The version of ctest is not able to handle intentionally failing "
           "tests, so pass.\n");
    return 0;
  }
  return argc;
}