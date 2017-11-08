static int fopen_works(void)
{
  FILE *fpa[3];
  int i;
  int ret = 1;

  for (i = 0; i < 3; i++) {
    fpa[i] = NULL;
  }
  for (i = 0; i < 3; i++) {
    fpa[i] = fopen(DEV_NULL, "r");
    if (fpa[i] == NULL) {
      store_errmsg("fopen() failed", ERRNO);
      fprintf(stderr, "%s\n", msgbuff);
      ret = 0;
      break;
    }
  }
  for (i = 0; i < 3; i++) {
    if (fpa[i] != NULL)
      fclose(fpa[i]);
  }
  return ret;
}