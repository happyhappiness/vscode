static void process_user_header (ENVELOPE *env)
{
  LIST *uh = UserHeader;
  LIST *last = env->userhdrs;

  if (last)
    while (last->next)
      last = last->next;

  for (; uh; uh = uh->next)
  {
    if (ascii_strncasecmp ("from:", uh->data, 5) == 0)
    {
      /* User has specified a default From: address.  Remove default address */
      rfc822_free_address (&env->from);
      env->from = rfc822_parse_adrlist (env->from, uh->data + 5);
    }
    else if (ascii_strncasecmp ("reply-to:", uh->data, 9) == 0)
    {
      rfc822_free_address (&env->reply_to);
      env->reply_to = rfc822_parse_adrlist (env->reply_to, uh->data + 9);
    }
    else if (ascii_strncasecmp ("message-id:", uh->data, 11) == 0)
    {
      char *tmp = mutt_extract_message_id (uh->data + 11, NULL);
      if (rfc822_valid_msgid (tmp) >= 0)
      {
	FREE(&env->message_id);
	env->message_id = tmp;
      } else
	FREE(&tmp);
    }
    else if (ascii_strncasecmp ("to:", uh->data, 3) != 0 &&
	     ascii_strncasecmp ("cc:", uh->data, 3) != 0 &&
	     ascii_strncasecmp ("bcc:", uh->data, 4) != 0 &&
	     ascii_strncasecmp ("subject:", uh->data, 8) != 0 &&
	     ascii_strncasecmp ("return-path:", uh->data, 12) != 0)
    {
      if (last)
      {
	last->next = mutt_new_list ();
	last = last->next;
      }
      else
	last = env->userhdrs = mutt_new_list ();
      last->data = safe_strdup (uh->data);
    }
  }
}