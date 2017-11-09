static void
END_PRIVILEGED (void)
{
#ifdef USE_SETGID
  if (DotlockFlags & DL_FL_USEPRIV)
  {
    if (SETEGID (UserGid) != 0)
    {
      /* perror ("setegid"); */
      exit (DL_EX_ERROR);
    }
  }
#endif
}