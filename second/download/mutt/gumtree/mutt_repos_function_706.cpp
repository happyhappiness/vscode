BODY *pgp_gpgme_encrypt_message (BODY *a, char *keylist, int sign)
{
  char *outfile = NULL;
  BODY *t;
  gpgme_key_t *rset = NULL;
  gpgme_data_t plaintext;
  
  rset = create_recipient_set (keylist, GPGME_PROTOCOL_OpenPGP);
  if (!rset)
    return NULL;
  
  if (sign)
    convert_to_7bit (a);
  plaintext = body_to_data_object (a, 0);
  if (!plaintext)
    {
      free_recipient_set (&rset);
      return NULL;
    }
  
  outfile = encrypt_gpgme_object (plaintext, rset, 0, sign);
  gpgme_data_release (plaintext);
  free_recipient_set (&rset);
  if (!outfile)
      return NULL;

  t = mutt_new_body ();
  t->type = TYPEMULTIPART;
  t->subtype = safe_strdup ("encrypted");
  t->encoding = ENC7BIT;
  t->use_disp = 0;
  t->disposition = DISPINLINE;

  mutt_generate_boundary(&t->parameter);
  mutt_set_parameter("protocol", "application/pgp-encrypted", &t->parameter);
  
  t->parts = mutt_new_body ();
  t->parts->type = TYPEAPPLICATION;
  t->parts->subtype = safe_strdup ("pgp-encrypted");
  t->parts->encoding = ENC7BIT;

  t->parts->next = mutt_new_body ();
  t->parts->next->type = TYPEAPPLICATION;
  t->parts->next->subtype = safe_strdup ("octet-stream");
  t->parts->next->encoding = ENC7BIT;
  t->parts->next->filename = outfile;
  t->parts->next->use_disp = 1;
  t->parts->next->disposition = DISPATTACH;
  t->parts->next->unlink = 1; /* delete after sending the message */
  t->parts->next->d_filename = safe_strdup ("msg.asc"); /* non pgp/mime
                                                           can save */

  return t;
}