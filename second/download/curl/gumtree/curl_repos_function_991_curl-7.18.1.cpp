int Curl_nss_init(void)
{
  if(!initialized)
    PR_Init(PR_USER_THREAD, PR_PRIORITY_NORMAL, 256);

  /* We will actually initialize NSS later */

  return 1;
}