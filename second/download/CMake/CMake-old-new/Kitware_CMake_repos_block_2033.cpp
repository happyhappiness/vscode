{
  int ii;

  printf("Command:");
  for (ii = 1; ii < argc; ++ii) {
    printf(" \"%s\"", argv[ii]);
  }
  printf("\n");

  return 42;
}