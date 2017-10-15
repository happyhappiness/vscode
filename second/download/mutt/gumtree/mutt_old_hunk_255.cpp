}

static void print_time(time_t t, STATE *s)
{
  char p[STRING];

  setlocale (LC_TIME, "");
#ifdef HAVE_LANGINFO_D_T_FMT
  strftime (p, sizeof (p), nl_langinfo (D_T_FMT), localtime (&t));
#else
  strftime (p, sizeof (p), "%c", localtime (&t));
#endif
  setlocale (LC_TIME, "C");
  state_attach_puts (p, s);
}

/* 
 * Implementation of `sign_message'.
 */

