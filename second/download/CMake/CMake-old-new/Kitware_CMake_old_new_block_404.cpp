{
  (void)argc; (void)argv;
  fprintf(stdout, "Output on stdout from grandchild before sleep.\n");
  fprintf(stderr, "Output on stderr from grandchild before sleep.\n");
  fflush(stdout);
  fflush(stderr);
  /* TODO: Instead of closing pipes here leave them open to make sure
     the grandparent can stop listening when the parent exits.  This
     part of the test cannot be enabled until the feature is
     implemented.  */
  fclose(stdout);
  fclose(stderr);
  testProcess_sleep(15);
  return 0;
}