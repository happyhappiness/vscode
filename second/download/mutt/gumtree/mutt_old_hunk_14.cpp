
  for (i = 0; i < idxlen; i++)
  {
    strfcpy(pretty, idx[i]->content->filename, sizeof(pretty));
    if(stat(idx[i]->content->filename, &st) != 0)
    {
      mutt_pretty_mailbox(pretty);
      mutt_error(_("%s [#%d] no longer exists!"),
		 pretty, i+1);
      return -1;
    }
    
    if(idx[i]->content->stamp < st.st_mtime)
    {
      mutt_pretty_mailbox(pretty);
      snprintf(msg, sizeof(msg), _("%s [#%d] modified. Update encoding?"),
	       pretty, i+1);
      
      if((r = mutt_yesorno(msg, M_YES)) == M_YES)
	mutt_update_encoding(idx[i]->content);
      else if(r == -1)
