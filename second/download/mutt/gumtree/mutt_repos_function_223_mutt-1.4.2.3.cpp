void pgp_extract_keys_from_messages (HEADER *h)
{
  int i;
  char tempfname[_POSIX_PATH_MAX];
  FILE *fpout;

  if (h)
  {
    mutt_parse_mime_message (Context, h);
    if(h->pgp & PGPENCRYPT && !pgp_valid_passphrase ())
      return;
  }

  mutt_mktemp (tempfname);
  if (!(fpout = safe_fopen (tempfname, "w")))
  {
    mutt_perror (tempfname);
    return;
  }

  set_option (OPTDONTHANDLEPGPKEYS);
  
  if (!h)
  {
    for (i = 0; i < Context->vcount; i++)
    {
      if (Context->hdrs[Context->v2r[i]]->tagged)
      {
	mutt_parse_mime_message (Context, Context->hdrs[Context->v2r[i]]);
	if (Context->hdrs[Context->v2r[i]]->pgp & PGPENCRYPT
	   && !pgp_valid_passphrase())
	{
	  fclose (fpout);
	  goto bailout;
	}
	mutt_copy_message (fpout, Context, Context->hdrs[Context->v2r[i]], 
			   M_CM_DECODE|M_CM_CHARCONV, 0);
      }
    }
  } 
  else
  {
    mutt_parse_mime_message (Context, h);
    if (h->pgp & PGPENCRYPT && !pgp_valid_passphrase())
    {
      fclose (fpout);
      goto bailout;
    }
    mutt_copy_message (fpout, Context, h, M_CM_DECODE|M_CM_CHARCONV, 0);
  }
      
  fclose (fpout);
  mutt_endwin (NULL);
  pgp_invoke_import (tempfname);
  mutt_any_key_to_continue (NULL);

  bailout:
  
  mutt_unlink (tempfname);
  unset_option (OPTDONTHANDLEPGPKEYS);
  
}