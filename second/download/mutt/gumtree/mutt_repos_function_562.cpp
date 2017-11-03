static int socket_preconnect (void)
{
  int rc;
  int save_errno;

  if (mutt_strlen (Preconnect))
  {
    dprint (2, (debugfile, "Executing preconnect: %s\n", Preconnect));
    rc = mutt_system (Preconnect);
    dprint (2, (debugfile, "Preconnect result: %d\n", rc));
    if (rc)
    {
      save_errno = errno;
      mutt_perror (_("Preconnect command failed."));
      mutt_sleep (1);
      
      return save_errno;
    }
  }

  return 0;
}