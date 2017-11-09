void crypt_extract_keys_from_messages (HEADER * h)
{
  int i;
  char tempfname[_POSIX_PATH_MAX], *mbox;
  ADDRESS *tmp = NULL;
  FILE *fpout;

  if (!WithCrypto)
    return;

  mutt_mktemp (tempfname, sizeof (tempfname));
  if (!(fpout = safe_fopen (tempfname, "w")))
  {
    mutt_perror (tempfname);
    return;
  }

  if ((WithCrypto & APPLICATION_PGP))
    set_option (OPTDONTHANDLEPGPKEYS);

  if (!h)
  {
    for (i = 0; i < Context->vcount; i++)
    {
      if (Context->hdrs[Context->v2r[i]]->tagged)
      {
	mutt_parse_mime_message (Context, Context->hdrs[Context->v2r[i]]);
	if (Context->hdrs[Context->v2r[i]]->security & ENCRYPT &&
	    !crypt_valid_passphrase (Context->hdrs[Context->v2r[i]]->security))
	{
	  safe_fclose (&fpout);
	  break;
	}

	if ((WithCrypto & APPLICATION_PGP)
            && (Context->hdrs[Context->v2r[i]]->security & APPLICATION_PGP))
	{
	  mutt_copy_message (fpout, Context, Context->hdrs[Context->v2r[i]], 
			     MUTT_CM_DECODE|MUTT_CM_CHARCONV, 0);
	  fflush(fpout);
	  
	  mutt_endwin (_("Trying to extract PGP keys...\n"));
	  crypt_pgp_invoke_import (tempfname);
	}

	if ((WithCrypto & APPLICATION_SMIME)
            && (Context->hdrs[Context->v2r[i]]->security & APPLICATION_SMIME))
	{
	  if (Context->hdrs[Context->v2r[i]]->security & ENCRYPT)
	    mutt_copy_message (fpout, Context, Context->hdrs[Context->v2r[i]],
			       MUTT_CM_NOHEADER|MUTT_CM_DECODE_CRYPT
                               |MUTT_CM_DECODE_SMIME, 0);
	  else
	    mutt_copy_message (fpout, Context,
			       Context->hdrs[Context->v2r[i]], 0, 0);
	  fflush(fpout);

          if (Context->hdrs[Context->v2r[i]]->env->from)
	    tmp = mutt_expand_aliases (Context->hdrs[Context->v2r[i]]->env->from);
	  else if (Context->hdrs[Context->v2r[i]]->env->sender)
	    tmp = mutt_expand_aliases (Context->hdrs[Context->v2r[i]]
                                                    ->env->sender);
          mbox = tmp ? tmp->mailbox : NULL;
	  if (mbox)
	  {
	    mutt_endwin (_("Trying to extract S/MIME certificates...\n"));
	    crypt_smime_invoke_import (tempfname, mbox);
	    tmp = NULL;
	  }
	}

	rewind (fpout);
      }
    }
  }
  else
  {
    mutt_parse_mime_message (Context, h);
    if (!(h->security & ENCRYPT && !crypt_valid_passphrase (h->security)))
    {
      if ((WithCrypto & APPLICATION_PGP)
          && (h->security & APPLICATION_PGP))
      {
	mutt_copy_message (fpout, Context, h, MUTT_CM_DECODE|MUTT_CM_CHARCONV, 0);
	fflush(fpout);
	mutt_endwin (_("Trying to extract PGP keys...\n"));
	crypt_pgp_invoke_import (tempfname);
      }

      if ((WithCrypto & APPLICATION_SMIME)
          && (h->security & APPLICATION_SMIME))
      {
	if (h->security & ENCRYPT)
	  mutt_copy_message (fpout, Context, h, MUTT_CM_NOHEADER
                                                |MUTT_CM_DECODE_CRYPT
                                                |MUTT_CM_DECODE_SMIME, 0);
	else
	  mutt_copy_message (fpout, Context, h, 0, 0);

	fflush(fpout);
	if (h->env->from) tmp = mutt_expand_aliases (h->env->from);
	else if (h->env->sender)  tmp = mutt_expand_aliases (h->env->sender); 
	mbox = tmp ? tmp->mailbox : NULL;
	if (mbox) /* else ? */
	{
	  mutt_message (_("Trying to extract S/MIME certificates...\n"));
	  crypt_smime_invoke_import (tempfname, mbox);
	}
      }
    }
  }
      
  safe_fclose (&fpout);
  if (isendwin())
    mutt_any_key_to_continue (NULL);

  mutt_unlink (tempfname);

  if ((WithCrypto & APPLICATION_PGP))
    unset_option (OPTDONTHANDLEPGPKEYS);
}