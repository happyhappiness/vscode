static int
mutt_nss_error (const char *call)
{
  mutt_error (_("%s failed (error %d)"), call, PR_GetError ());
  return -1;
}