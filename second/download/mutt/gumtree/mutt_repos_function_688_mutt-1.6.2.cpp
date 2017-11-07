BODY *smime_gpgme_build_smime_entity (BODY *a, char *keylist)
{
  char *outfile = NULL;
  BODY *t;
  gpgme_key_t *rset = NULL;
  gpgme_data_t plaintext;

  rset = create_recipient_set (keylist, GPGME_PROTOCOL_CMS);
  if (!rset)
    return NULL;

  plaintext = body_to_data_object (a, 0);
  if (!plaintext)
    {
      free_recipient_set (&rset);
      return NULL;
    }

  outfile = encrypt_gpgme_object (plaintext, rset, 1, 0);
  gpgme_data_release (plaintext);
  free_recipient_set (&rset);
  if (!outfile) 
      return NULL;

  t = mutt_new_body ();
  t->type = TYPEAPPLICATION;
  t->subtype = safe_strdup ("pkcs7-mime");
  mutt_set_parameter ("name", "smime.p7m", &t->parameter);
  mutt_set_parameter ("smime-type", "enveloped-data", &t->parameter);
  t->encoding = ENCBASE64;  /* The output of OpenSSL SHOULD be binary */
  t->use_disp = 1;
  t->disposition = DISPATTACH;
  t->d_filename = safe_strdup ("smime.p7m");
  t->filename = outfile;
  t->unlink = 1; /*delete after sending the message */
  t->parts=0;
  t->next=0;
  
  return t;
}