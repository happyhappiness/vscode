static int progress_callback(void *clientp, double dltotal, double dlnow,
                             double ultotal, double ulnow)
{
  FILE *moo;
  static int prev_ultotal = -1;
  static int prev_ulnow = -1;
  (void)clientp; /* UNUSED */
  (void)dltotal; /* UNUSED */
  (void)dlnow; /* UNUSED */

  /* to avoid depending on timing, which will cause this progress function to
     get called a different number of times depending on circumstances, we
     only log these lines if the numbers are different from the previous
     invoke */
  if((prev_ultotal != (int)ultotal) ||
     (prev_ulnow != (int)ulnow)) {

    moo = fopen(libtest_arg2, "ab");
    if(moo) {
      fprintf(moo, "Progress callback called with UL %d out of %d\n",
              (int)ulnow, (int)ultotal);
      fclose(moo);
    }
    prev_ulnow = (int) ulnow;
    prev_ultotal = (int) ultotal;
  }
  return 0;
}