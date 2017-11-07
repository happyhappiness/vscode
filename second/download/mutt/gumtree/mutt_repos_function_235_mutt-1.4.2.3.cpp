int pgp_protect (HEADER *msg, char *pgpkeylist)
{
  BODY *pbody = NULL;
  int flags = msg->pgp;
  int traditional = 0;
  int i;

  if ((msg->pgp & PGPSIGN) && !pgp_valid_passphrase ())
    return (-1);

  if ((msg->content->type == TYPETEXT) &&
      !ascii_strcasecmp (msg->content->subtype, "plain") &&
      ((flags & PGPENCRYPT) || (msg->content->content && msg->content->content->hibin == 0)))
  {
    if ((i = query_quadoption (OPT_PGPTRADITIONAL, _("Create an application/pgp message?"))) == -1)
      return -1;
    else if (i == M_YES)
      traditional = 1;
  }

  mutt_message _("Invoking PGP...");

  if (!isendwin ())
    mutt_endwin (NULL);

  if (traditional)
  {
    if (!(pbody = pgp_traditional_encryptsign (msg->content, flags, pgpkeylist)))
      return -1;
    
    msg->content = pbody;
    return 0;
  }

  if ((flags & PGPSIGN) && (!(flags & PGPENCRYPT) || option (OPTPGPRETAINABLESIG)))
  {
    if (!(pbody = pgp_sign_message (msg->content)))
      return -1;

    msg->content = pbody;
    flags &= ~PGPSIGN;
  }

  if (flags & PGPENCRYPT)
  {
    if (!(pbody = pgp_encrypt_message (msg->content, pgpkeylist, flags & PGPSIGN)))
    {

      /* did we perform a retainable signature? */
      if (flags != msg->pgp)
      {
	/* remove the outer multipart layer */
	msg->content = mutt_remove_multipart (msg->content);
	/* get rid of the signature */
	mutt_free_body (&msg->content->next);
      }

      return (-1);
    }

    /* destroy temporary signature envelope when doing retainable 
     * signatures.
     */
    if (flags != msg->pgp)
    {
      mutt_remove_multipart (msg->content);
      mutt_free_body (&msg->content->next);
    }
    
    msg->content = pbody;
  }

  return (0);
}