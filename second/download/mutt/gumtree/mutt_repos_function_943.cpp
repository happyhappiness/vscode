int mix_send_message (LIST *chain, const char *tempfile)
{
  char cmd[HUGE_STRING];
  char tmp[HUGE_STRING];
  char cd_quoted[STRING];
  int i;

  snprintf (cmd, sizeof (cmd), "cat %s | %s -m ", tempfile, Mixmaster);
  
  for (i = 0; chain; chain = chain->next, i = 1)
  {
    strfcpy (tmp, cmd, sizeof (tmp));
    mutt_quote_filename (cd_quoted, sizeof (cd_quoted), (char *) chain->data);
    snprintf (cmd, sizeof (cmd), "%s%s%s", tmp, i ? "," : " -l ", cd_quoted);
  }

  if (!option (OPTNOCURSES))
    mutt_endwin (NULL);
  
  if ((i = mutt_system (cmd)))
  {
    fprintf (stderr, _("Error sending message, child exited %d.\n"), i);
    if (!option (OPTNOCURSES))
    {
      mutt_any_key_to_continue (NULL);
      mutt_error _("Error sending message.");
    }
  }

  unlink (tempfile);
  return i;
}