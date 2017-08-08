{
  if (ac <= 1) {
    printf("Usage: %s <file>\n", av[0]);
    return 1;
  }
  if (!FileExists(av[1])) {
    printf("Missing file %s\n", av[1]);
    return 1;
  }
  if (FileExists(av[2])) {
    printf("File %s should be in subdirectory\n", av[2]);
    return 1;
  }
  printf("%s is not there! Good.", av[2]);
  printf("%s is there! Good.", av[1]);
  return 0;
}