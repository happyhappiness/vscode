void mutt_unprepare_envelope (ENVELOPE *env)
{
  LIST *item;

  for (item = env->userhdrs; item; item = item->next)
    rfc2047_decode (&item->data);

  rfc822_free_address (&env->mail_followup_to);

  /* back conversions */
  rfc2047_decode_adrlist (env->to);
  rfc2047_decode_adrlist (env->cc);
  rfc2047_decode_adrlist (env->bcc);
  rfc2047_decode_adrlist (env->from);
  rfc2047_decode_adrlist (env->reply_to);
  rfc2047_decode (&env->subject);
  rfc2047_decode (&env->x_label);
}