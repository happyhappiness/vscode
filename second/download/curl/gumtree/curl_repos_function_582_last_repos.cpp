static int progress_callback(void *clientp, double dltotal, double dlnow,
                             double ultotal, double ulnow)
{
  FILE *moo = fopen(libtest_arg2, "wb");

  (void)clientp; /* UNUSED */
  (void)dltotal; /* UNUSED */
  (void)dlnow; /* UNUSED */

  if(moo) {
    if((size_t)ultotal == data_size && (size_t)ulnow == data_size)
      fprintf(moo, "PASSED, UL data matched data size\n");
    else
      fprintf(moo, "Progress callback called with UL %f out of %f\n",
              ulnow, ultotal);
    fclose(moo);
  }
  return 0;
}