static void process_user_recips (ENVELOPE *env)
{
  LIST *uh = UserHeader;

  for (; uh; uh = uh->next)
  {
    if (ascii_strncasecmp ("to:", uh->data, 3) == 0)
      env->to = rfc822_parse_adrlist (env->to, uh->data + 3);
    else if (ascii_strncasecmp ("cc:", uh->data, 3) == 0)
      env->cc = rfc822_parse_adrlist (env->cc, uh->data + 3);
    else if (ascii_strncasecmp ("bcc:", uh->data, 4) == 0)
      env->bcc = rfc822_parse_adrlist (env->bcc, uh->data + 4);
  }
}