  char buf[2048];
  const char *cwd = Getcwd(buf, sizeof(buf));

  fprintf(stdout, "Working directory: -->%s<--", cwd);

  return 0;
}