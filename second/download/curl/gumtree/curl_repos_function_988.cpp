static int
krb5_check_prot(void *app_data, int level)
{
  (void)app_data; /* unused */
  if(level == PROT_CONFIDENTIAL)
    return -1;
  return 0;
}