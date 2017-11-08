static int
krb4_overhead(void *app_data, int level, int len)
{
  /* no arguments are used, just init them to prevent compiler warnings */
  app_data = NULL;
  level = 0;
  len = 0;
  return 31;
}