void mutt_pipe_attachment_list (FILE *fp, int tag, BODY *top, int filter)
{
  STATE state;
  char buf[SHORT_STRING];
  pid_t thepid;

  if (fp)
    filter = 0; /* sanity check: we can't filter in the recv case yet */

  buf[0] = 0;
  memset (&state, 0, sizeof (STATE));

  if (mutt_get_field ((filter ? _("Filter through: ") : _("Pipe to: ")),
				  buf, sizeof (buf), MUTT_CMD) != 0 || !buf[0])
    return;

  mutt_expand_path (buf, sizeof (buf));

  if (!filter && !option (OPTATTACHSPLIT))
  {
    mutt_endwin (NULL);
    thepid = mutt_create_filter (buf, &state.fpout, NULL, NULL);
    pipe_attachment_list (buf, fp, tag, top, filter, &state);
    safe_fclose (&state.fpout);
    if (mutt_wait_filter (thepid) != 0 || option (OPTWAITKEY))
      mutt_any_key_to_continue (NULL);
  }
  else
    pipe_attachment_list (buf, fp, tag, top, filter, &state);
}