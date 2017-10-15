#define CURHDR Context->hdrs[Context->v2r[menu->current]]
#define OLDHDR Context->hdrs[Context->v2r[menu->oldcurrent]]
#define UNREAD(h) mutt_thread_contains_unread (Context, h)

extern size_t UngetCount;

/* de facto standard escapes for tsl/fsl */
static char *tsl = "\033]0;";
static char *fsl = "\007";

/* terminal status capability check. terminfo must have been initialized. */
short mutt_ts_capability(void)
{
  char *term = getenv("TERM");
  char *tcaps;
  int tcapi;
  char **termp;
  char *known[] = {
    "color-xterm",
    "cygwin",
    "eterm",
    "kterm",
    "nxterm",
    "putty",
    "rxvt",
    "screen",
    "xterm",
    NULL
  };

  /* If tsl is set, then terminfo says that status lines work. */
  tcaps = tigetstr("tsl");
  if (tcaps && tcaps != (char *)-1 && *tcaps)
  {
    /* update the static defns of tsl/fsl from terminfo */
    tsl = safe_strdup(tcaps);

    tcaps = tigetstr("fsl");
    if (tcaps && tcaps != (char *)-1 && *tcaps)
      fsl = safe_strdup(tcaps);

    return 1;
  }

  /* If XT (boolean) is set, then this terminal supports the standard escape. */
  /* Beware: tigetflag returns -1 if XT is invalid or not a boolean. */
#ifdef HAVE_USE_EXTENDED_NAMES
  use_extended_names (TRUE);
  tcapi = tigetflag("XT");
  if (tcapi == 1)
    return 1;
#endif /* HAVE_USE_EXTENDED_NAMES */

  /* Check term types that are known to support the standard escape without
   * necessarily asserting it in terminfo. */
  for (termp = known; termp; termp++)
  {
    if (term && *termp && mutt_strncasecmp (term, *termp, strlen(*termp)))
      return 1;
  }

  /* not supported */
  return 0;
}

void mutt_ts_status(char *str)
{
  /* If empty, do not set.  To clear, use a single space. */
  if (str == NULL || *str == '\0')
    return;
  fprintf(stderr, "%s%s%s", tsl, str, fsl);
}

void mutt_ts_icon(char *str)
{
  /* If empty, do not set.  To clear, use a single space. */
  if (str == NULL || *str == '\0')
    return;

  /* icon setting is not supported in terminfo, so hardcode the escape - yuck */
  fprintf(stderr, "\033]1;%s\007", str);
}

void index_make_entry (char *s, size_t l, MUTTMENU *menu, int num)
{
  format_flag flag = M_FORMAT_MAKEPRINT | M_FORMAT_ARROWCURSOR | M_FORMAT_INDEX;
  int edgemsgno, reverse = Sort & SORT_REVERSE;
  HEADER *h = Context->hdrs[Context->v2r[num]];
  THREAD *tmp;
