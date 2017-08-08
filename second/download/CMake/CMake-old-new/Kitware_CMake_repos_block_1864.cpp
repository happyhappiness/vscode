{
    if (strcmp(env, "1") == 0) {
      oldCtest = 1;
    }
    printf("DASHBOARD_TEST_FROM_CTEST = %s\n", env);
  }