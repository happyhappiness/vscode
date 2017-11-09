static void
BEGIN_PRIVILEGED (void)
{
#ifdef USE_SETGID
  if (DotlockFlags & DL_FL_USEPRIV)
  {
    if (SETEGID (MailGid) != 0)
    {
      /* perror ("setegid"); */
      exit (DL_EX_ERROR);
    }
  }
#endif
}