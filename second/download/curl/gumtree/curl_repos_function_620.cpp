static int
krb4_check_prot(void *app_data, int level)
{
  app_data = NULL; /* prevent compiler warning */
  if(level == prot_confidential)
    return -1;
  return 0;
}