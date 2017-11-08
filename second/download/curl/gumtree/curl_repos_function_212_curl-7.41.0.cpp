static void remsock(int *f, GlobalInfo *g)
{
  fprintf(MSG_OUT, "\nremsock: ");

  if(f)
  {
    free(f);
  }
}