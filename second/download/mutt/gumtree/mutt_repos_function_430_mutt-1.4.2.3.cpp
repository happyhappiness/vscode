static void be_print_header (ENVELOPE *env)
{
  char tmp[HUGE_STRING];

  if (env->to)
  {
    addstr ("To: ");
    tmp[0] = 0;
    rfc822_write_address (tmp, sizeof (tmp), env->to);
    addstr (tmp);
    addch ('\n');
  }
  if (env->cc)
  {
    addstr ("Cc: ");
    tmp[0] = 0;
    rfc822_write_address (tmp, sizeof (tmp), env->cc);
    addstr (tmp);
    addch ('\n');
  }
  if (env->bcc)
  {
    addstr ("Bcc: ");
    tmp[0] = 0;
    rfc822_write_address (tmp, sizeof (tmp), env->bcc);
    addstr (tmp);
    addch ('\n');
  }
  if (env->subject)
  {
    addstr ("Subject: ");
    addstr (env->subject);
    addch ('\n');
  }
  addch ('\n');
}