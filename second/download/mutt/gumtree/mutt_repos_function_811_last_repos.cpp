static int
check_attachments(ATTACH_CONTEXT *actx)
{
  int i, r;
  struct stat st;
  char pretty[_POSIX_PATH_MAX], msg[_POSIX_PATH_MAX + SHORT_STRING];

  for (i = 0; i < actx->idxlen; i++)
  {
    strfcpy(pretty, actx->idx[i]->content->filename, sizeof(pretty));
    if(stat(actx->idx[i]->content->filename, &st) != 0)
    {
      mutt_pretty_mailbox(pretty, sizeof (pretty));
      mutt_error(_("%s [#%d] no longer exists!"),
		 pretty, i+1);
      return -1;
    }
    
    if(actx->idx[i]->content->stamp < st.st_mtime)
    {
      mutt_pretty_mailbox(pretty, sizeof (pretty));
      snprintf(msg, sizeof(msg), _("%s [#%d] modified. Update encoding?"),
	       pretty, i+1);
      
      if((r = mutt_yesorno(msg, MUTT_YES)) == MUTT_YES)
	mutt_update_encoding(actx->idx[i]->content);
      else if(r == -1)
	return -1;
    }
  }

  return 0;
}