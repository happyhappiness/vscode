int mutt_sasl_interact (sasl_interact_t* interaction)
{
  char prompt[SHORT_STRING];
  char resp[SHORT_STRING];

  while (interaction->id != SASL_CB_LIST_END)
  {
    dprint (2, (debugfile, "mutt_sasl_interact: filling in SASL interaction %ld.\n", interaction->id));

    snprintf (prompt, sizeof (prompt), "%s: ", interaction->prompt);
    resp[0] = '\0';
    if (option (OPTNOCURSES) || mutt_get_field (prompt, resp, sizeof (resp), 0))
      return SASL_FAIL;

    interaction->len = mutt_strlen (resp)+1;
    interaction->result = safe_malloc (interaction->len);
    memcpy ((char *)interaction->result, resp, interaction->len);

    interaction++;
  }

  return SASL_OK;
}