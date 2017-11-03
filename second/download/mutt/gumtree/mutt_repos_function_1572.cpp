int crypt_get_keys (HEADER *msg, char **keylist, int oppenc_mode)
{
  ADDRESS *adrlist = NULL, *last = NULL;
  const char *fqdn = mutt_fqdn (1);

  /* Do a quick check to make sure that we can find all of the encryption
   * keys if the user has requested this service.
   */

  if (!WithCrypto)
    return 0;

  if ((WithCrypto & APPLICATION_PGP))
    set_option (OPTPGPCHECKTRUST);

  last = rfc822_append (&adrlist, msg->env->to, 0);
  last = rfc822_append (last ? &last : &adrlist, msg->env->cc, 0);
  rfc822_append (last ? &last : &adrlist, msg->env->bcc, 0);

  if (fqdn)
    rfc822_qualify (adrlist, fqdn);
  adrlist = mutt_remove_duplicates (adrlist);

  *keylist = NULL;

  if (oppenc_mode || (msg->security & ENCRYPT))
  {
     if ((WithCrypto & APPLICATION_PGP)
         && (msg->security & APPLICATION_PGP))
     {
       if ((*keylist = crypt_pgp_findkeys (adrlist, oppenc_mode)) == NULL)
       {
           rfc822_free_address (&adrlist);
           return (-1);
       }
       unset_option (OPTPGPCHECKTRUST);
     }
     if ((WithCrypto & APPLICATION_SMIME)
         && (msg->security & APPLICATION_SMIME))
     {
       if ((*keylist = crypt_smime_findkeys (adrlist, oppenc_mode)) == NULL)
       {
           rfc822_free_address (&adrlist);
           return (-1);
       }
     }
  }

  rfc822_free_address (&adrlist);
    
  return (0);
}