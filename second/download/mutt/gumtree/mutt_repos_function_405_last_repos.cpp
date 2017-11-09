int smime_valid_passphrase (void)
{
  time_t now = time (NULL);

  if (now < SmimeExptime)
    /* Use cached copy.  */
    return 1;

  smime_void_passphrase();
  
  if (mutt_get_password (_("Enter S/MIME passphrase:"), SmimePass, sizeof (SmimePass)) == 0)
    {
      SmimeExptime = time (NULL) + SmimeTimeout;
      return (1);
    }
  else
    SmimeExptime = 0;

  return 0;
}