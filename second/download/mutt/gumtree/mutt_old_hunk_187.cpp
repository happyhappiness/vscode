    if(idx[i]->content->stamp < st.st_mtime)
    {
      mutt_pretty_mailbox(pretty, sizeof (pretty));
      snprintf(msg, sizeof(msg), _("%s [#%d] modified. Update encoding?"),
	       pretty, i+1);
      
      if((r = mutt_yesorno(msg, M_YES)) == M_YES)
	mutt_update_encoding(idx[i]->content);
      else if(r == -1)
	return -1;
    }
  }

