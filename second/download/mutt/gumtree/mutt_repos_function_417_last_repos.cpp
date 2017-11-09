smime_key_t *smime_ask_for_key(char *prompt, short abilities, short public)
{
  smime_key_t *key;
  char resp[SHORT_STRING];

  if (!prompt) prompt = _("Enter keyID: ");

  mutt_clear_error ();

  FOREVER
  {
    resp[0] = 0;
    if (mutt_get_field (prompt, resp, sizeof (resp), MUTT_CLEAR) != 0)
      return NULL;

    if ((key = smime_get_key_by_str (resp, abilities, public)))
      return key;

    BEEP ();
  }
}