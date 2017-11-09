void mutt_prepare_envelope (ENVELOPE *env, int final)
{
  char buffer[LONG_STRING];

  if (final)
  {
    if (env->bcc && !(env->to || env->cc))
    {
      /* some MTA's will put an Apparently-To: header field showing the Bcc:
       * recipients if there is no To: or Cc: field, so attempt to suppress
       * it by using an empty To: field.
       */
      env->to = rfc822_new_address ();
      env->to->group = 1;
      env->to->next = rfc822_new_address ();

      buffer[0] = 0;
      rfc822_cat (buffer, sizeof (buffer), "undisclosed-recipients",
		  RFC822Specials);

      env->to->mailbox = safe_strdup (buffer);
    }

    mutt_set_followup_to (env);

    if (!env->message_id)
      env->message_id = mutt_gen_msgid ();
  }

  /* Take care of 8-bit => 7-bit conversion. */
  rfc2047_encode_adrlist (env->to, "To");
  rfc2047_encode_adrlist (env->cc, "Cc");
  rfc2047_encode_adrlist (env->bcc, "Bcc");
  rfc2047_encode_adrlist (env->from, "From");
  rfc2047_encode_adrlist (env->mail_followup_to, "Mail-Followup-To");
  rfc2047_encode_adrlist (env->reply_to, "Reply-To");
  rfc2047_encode_string (&env->x_label);

  if (env->subject)
  {
    rfc2047_encode_string (&env->subject);
  }
  encode_headers (env->userhdrs);
}