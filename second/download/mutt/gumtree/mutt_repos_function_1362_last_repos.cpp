static void mutt_generate_recvattach_list (ATTACH_CONTEXT *actx,
                                           HEADER *hdr,
                                           BODY *m,
                                           FILE *fp,
                                           int parent_type,
                                           int level,
                                           int decrypted)
{
  ATTACHPTR *new;
  BODY *new_body = NULL;
  FILE *new_fp = NULL;
  int need_secured, secured;

  for (; m; m = m->next)
  {
    need_secured = secured = 0;

    if ((WithCrypto & APPLICATION_SMIME) &&
        mutt_is_application_smime (m))
    {
      need_secured = 1;

      if (!crypt_valid_passphrase (APPLICATION_SMIME))
        goto decrypt_failed;

      if (hdr->env)
        crypt_smime_getkeys (hdr->env);

      secured = !crypt_smime_decrypt_mime (fp, &new_fp, m, &new_body);

      /* S/MIME nesting */
      if ((mutt_is_application_smime (new_body) & SMIMEOPAQUE))
      {
        BODY *outer_new_body = new_body;
        FILE *outer_fp = new_fp;

        new_body = NULL;
        new_fp = NULL;

        secured = !crypt_smime_decrypt_mime (outer_fp, &new_fp, outer_new_body,
                                               &new_body);

        mutt_free_body (&outer_new_body);
        safe_fclose (&outer_fp);
      }

      if (secured)
        hdr->security |= SMIMEENCRYPT;
    }

    if ((WithCrypto & APPLICATION_PGP) &&
        (mutt_is_multipart_encrypted (m) ||
         mutt_is_malformed_multipart_pgp_encrypted (m)))
    {
      need_secured = 1;

      if (!crypt_valid_passphrase (APPLICATION_PGP))
        goto decrypt_failed;

      secured = !crypt_pgp_decrypt_mime (fp, &new_fp, m, &new_body);

      if (secured)
        hdr->security |= PGPENCRYPT;
    }

    if (need_secured && secured)
    {
      mutt_actx_add_fp (actx, new_fp);
      mutt_actx_add_body (actx, new_body);
      mutt_generate_recvattach_list (actx, hdr, new_body, new_fp, parent_type, level, 1);
      continue;
    }

decrypt_failed:
    /* Fall through and show the original parts if decryption fails */
    if (need_secured && !secured)
      mutt_error _("Can't decrypt encrypted message!");

    /* Strip out the top level multipart */
    if (m->type == TYPEMULTIPART &&
        m->parts &&
        !need_secured &&
        (parent_type == -1 && ascii_strcasecmp ("alternative", m->subtype)))
    {
      mutt_generate_recvattach_list (actx, hdr, m->parts, fp, m->type, level, decrypted);
    }
    else
    {
      new = (ATTACHPTR *) safe_calloc (1, sizeof (ATTACHPTR));
      mutt_actx_add_attach (actx, new);

      new->content = m;
      new->fp = fp;
      m->aptr = new;
      new->parent_type = parent_type;
      new->level = level;
      new->decrypted = decrypted;

      if (m->type == TYPEMULTIPART)
        mutt_generate_recvattach_list (actx, hdr, m->parts, fp, m->type, level + 1, decrypted);
      else if (mutt_is_message_type (m->type, m->subtype))
      {
        mutt_generate_recvattach_list (actx, m->hdr, m->parts, fp, m->type, level + 1, decrypted);
        hdr->security |= m->hdr->security;
      }
    }
  }
}