void mutt_print_attachment_list (FILE *fp, int tag, BODY *top)
{
  STATE state;
  
  pid_t thepid;
  if (query_quadoption (OPT_PRINT, tag ? _("Print tagged attachment(s)?") : _("Print attachment?")) != MUTT_YES)
    return;

  if (!option (OPTATTACHSPLIT))
  {
    if (!can_print (top, tag))
      return;
    mutt_endwin (NULL);
    memset (&state, 0, sizeof (STATE));
    thepid = mutt_create_filter (NONULL (PrintCmd), &state.fpout, NULL, NULL);
    print_attachment_list (fp, tag, top, &state);
    safe_fclose (&state.fpout);
    if (mutt_wait_filter (thepid) != 0 || option (OPTWAITKEY))
      mutt_any_key_to_continue (NULL);
  }
  else
    print_attachment_list (fp, tag, top, &state);
}