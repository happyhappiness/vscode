int mutt_protect (HEADER *msg, char *keylist)
{
  BODY *pbody = NULL, *tmp_pbody = NULL;
  BODY *tmp_smime_pbody = NULL;
  BODY *tmp_pgp_pbody = NULL;
  int flags = (WithCrypto & APPLICATION_PGP)? msg->security: 0;
  int i;

  if (!WithCrypto)
    return -1;

  if (!(msg->security & (ENCRYPT | SIGN)))
    return 0;

  if ((msg->security & SIGN) && !crypt_valid_passphrase (msg->security))
    return (-1);

  if ((WithCrypto & APPLICATION_PGP) && ((msg->security & PGPINLINE) == PGPINLINE))
  {
    if ((msg->content->type != TYPETEXT) ||
        ascii_strcasecmp (msg->content->subtype, "plain"))
    {
      if ((i = query_quadoption (OPT_PGPMIMEAUTO,
              _("Inline PGP can't be used with attachments.  Revert to PGP/MIME?"))) != MUTT_YES)
      {
        mutt_error _("Mail not sent: inline PGP can't be used with attachments.");
        return -1;
      }
    }
    else
    {
      /* they really want to send it inline... go for it */
      if (!isendwin ()) mutt_endwin _("Invoking PGP...");
      pbody = crypt_pgp_traditional_encryptsign (msg->content, flags, keylist);
      if (pbody)
      {
        msg->content = pbody;
        return 0;
      }

      /* otherwise inline won't work...ask for revert */
      if ((i = query_quadoption (OPT_PGPMIMEAUTO, _("Message can't be sent inline.  Revert to using PGP/MIME?"))) != MUTT_YES)
      {
        mutt_error _("Mail not sent.");
        return -1;
      }
    }

    /* go ahead with PGP/MIME */
  }

  if (!isendwin ()) mutt_endwin (NULL);

  if ((WithCrypto & APPLICATION_SMIME))
    tmp_smime_pbody = msg->content;
  if ((WithCrypto & APPLICATION_PGP))
    tmp_pgp_pbody   = msg->content;

  if (option (OPTCRYPTUSEPKA) && (msg->security & SIGN))
    {
      /* Set sender (necessary for e.g. PKA).  */

      if ((WithCrypto & APPLICATION_SMIME)
	  && (msg->security & APPLICATION_SMIME))
	crypt_smime_set_sender (msg->env->from->mailbox);
      else if ((WithCrypto & APPLICATION_PGP)
	  && (msg->security & APPLICATION_PGP))
	crypt_pgp_set_sender (msg->env->from->mailbox);
    }

  if (msg->security & SIGN)
  {
    if ((WithCrypto & APPLICATION_SMIME)
        && (msg->security & APPLICATION_SMIME))
    {
      if (!(tmp_pbody = crypt_smime_sign_message (msg->content)))
	return -1;
      pbody = tmp_smime_pbody = tmp_pbody;
    }

    if ((WithCrypto & APPLICATION_PGP)
        && (msg->security & APPLICATION_PGP)
        && (!(flags & ENCRYPT) || option (OPTPGPRETAINABLESIG)))
    {
      if (!(tmp_pbody = crypt_pgp_sign_message (msg->content)))
        return -1;

      flags &= ~SIGN;
      pbody = tmp_pgp_pbody = tmp_pbody;
    }

    if (WithCrypto
        && (msg->security & APPLICATION_SMIME)
	&& (msg->security & APPLICATION_PGP))
    {
	/* here comes the draft ;-) */
    }
  }


  if (msg->security & ENCRYPT)
  {
    if ((WithCrypto & APPLICATION_SMIME)
        && (msg->security & APPLICATION_SMIME))
    {
      if (!(tmp_pbody = crypt_smime_build_smime_entity (tmp_smime_pbody,
                                                        keylist)))
      {
	/* signed ? free it! */
	return (-1);
      }
      /* free tmp_body if messages was signed AND encrypted ... */
      if (tmp_smime_pbody != msg->content && tmp_smime_pbody != tmp_pbody)
      {
	/* detatch and don't delete msg->content,
	   which tmp_smime_pbody->parts after signing. */
	tmp_smime_pbody->parts = tmp_smime_pbody->parts->next;
	msg->content->next = NULL;
	mutt_free_body (&tmp_smime_pbody);
      }
      pbody = tmp_pbody;
    }

    if ((WithCrypto & APPLICATION_PGP)
        && (msg->security & APPLICATION_PGP))
    {
      if (!(pbody = crypt_pgp_encrypt_message (tmp_pgp_pbody, keylist,
                                               flags & SIGN)))
      {

	/* did we perform a retainable signature? */
	if (flags != msg->security)
	{
	  /* remove the outer multipart layer */
	  tmp_pgp_pbody = mutt_remove_multipart (tmp_pgp_pbody);
	  /* get rid of the signature */
	  mutt_free_body (&tmp_pgp_pbody->next);
	}

	return (-1);
      }

      /* destroy temporary signature envelope when doing retainable 
       * signatures.

       */
      if (flags != msg->security)
      {
	tmp_pgp_pbody = mutt_remove_multipart (tmp_pgp_pbody);
	mutt_free_body (&tmp_pgp_pbody->next);
      }
    }
  }

  if(pbody)
      msg->content = pbody;

  return 0;
}