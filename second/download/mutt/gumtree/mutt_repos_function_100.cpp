int mutt_resend_message (FILE *fp, CONTEXT *ctx, HEADER *cur)
{
  HEADER *msg = mutt_new_header ();
  
  if (mutt_prepare_template (fp, ctx, msg, cur, 1) < 0)
    return -1;

  if (WithCrypto)
  {
    /* mutt_prepare_template doesn't always flip on an application bit.
     * so fix that here */
    if (!(msg->security & (APPLICATION_SMIME | APPLICATION_PGP)))
    {
      if ((WithCrypto & APPLICATION_SMIME) && option (OPTSMIMEISDEFAULT))
        msg->security |= APPLICATION_SMIME;
      else if (WithCrypto & APPLICATION_PGP)
        msg->security |= APPLICATION_PGP;
      else
        msg->security |= APPLICATION_SMIME;
    }

    if (option (OPTCRYPTOPPORTUNISTICENCRYPT))
    {
      msg->security |= OPPENCRYPT;
      crypt_opportunistic_encrypt(msg);
    }
  }

  return ci_send_message (SENDRESEND, msg, NULL, ctx, cur);
}