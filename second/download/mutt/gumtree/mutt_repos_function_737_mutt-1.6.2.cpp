BODY *pgp_gpgme_make_key_attachment (char *tempf)
{
  crypt_key_t *key = NULL;
  gpgme_ctx_t context = NULL;
  gpgme_key_t export_keys[2];
  gpgme_data_t keydata = NULL;
  gpgme_error_t err;
  BODY *att = NULL;
  char buff[LONG_STRING];
  struct stat sb;

  unset_option (OPTPGPCHECKTRUST);

  key = crypt_ask_for_key (_("Please enter the key ID: "), NULL, 0,
                           APPLICATION_PGP, NULL);
  if (!key)
    goto bail;
  export_keys[0] = key->kobj;
  export_keys[1] = NULL;

  context = create_gpgme_context (0);
  gpgme_set_armor (context, 1);
  keydata = create_gpgme_data ();
  err = gpgme_op_export_keys (context, export_keys, 0, keydata);
  if (err != GPG_ERR_NO_ERROR)
  {
    mutt_error (_("Error exporting key: %s\n"), gpgme_strerror (err));
    mutt_sleep (1);
    goto bail;
  }

  tempf = data_object_to_tempfile (keydata, tempf, NULL);
  if (!tempf)
    goto bail;

  att = mutt_new_body ();
  /* tempf is a newly allocated string, so this is correct: */
  att->filename = tempf;
  att->unlink = 1;
  att->use_disp = 0;
  att->type = TYPEAPPLICATION;
  att->subtype = safe_strdup ("pgp-keys");
  /* L10N:
     MIME description for exported (attached) keys.
     You can translate this entry to a non-ASCII string (it will be encoded),
     but it may be safer to keep it untranslated. */
  snprintf (buff, sizeof (buff), _("PGP Key 0x%s."), crypt_keyid (key));
  att->description = safe_strdup (buff);
  mutt_update_encoding (att);

  stat (tempf, &sb);
  att->length = sb.st_size;

bail:
  crypt_free_key (&key);
  gpgme_data_release (keydata);
  gpgme_release (context);

  return att;
}