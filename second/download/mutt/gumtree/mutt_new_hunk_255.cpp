}

static void print_time(time_t t, STATE *s)
{
  char p[STRING];

#ifdef HAVE_LANGINFO_D_T_FMT
  strftime (p, sizeof (p), nl_langinfo (D_T_FMT), localtime (&t));
#else
  strftime (p, sizeof (p), "%c", localtime (&t));
#endif
  state_puts (p, s);
}

/* 
 * Implementation of `sign_message'.
 */

