void mutt_gpgme_set_sender (const char *sender)
{
  mutt_error ("[setting sender] mailbox: %s\n", sender);
  FREE (&current_sender);
  current_sender = safe_strdup (sender);
}