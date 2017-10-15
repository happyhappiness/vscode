#endif

#ifdef HAVE_SYS_RESOURCE_H
# include <sys/resource.h>
#endif

#ifdef HAVE_PGP


char PgpPass[STRING];
static time_t PgpExptime = 0; /* when does the cached passphrase expire? */

void pgp_void_passphrase (void)
{
  memset (PgpPass, 0, sizeof (PgpPass));
  PgpExptime = 0;
}

# if defined(HAVE_SETRLIMIT) && (!defined(DEBUG))

static void disable_coredumps (void)
{
  struct rlimit rl = {0, 0};
  static short done = 0;

  if (!done)
  {
    setrlimit (RLIMIT_CORE, &rl);
    done = 1;
  }
}

# endif /* HAVE_SETRLIMIT */

int pgp_valid_passphrase (void)
{
  time_t now = time (NULL);

# if defined(HAVE_SETRLIMIT) && (!defined(DEBUG))
  disable_coredumps ();
# endif

  if (now < PgpExptime) return 1; /* just use the cached copy. */
  pgp_void_passphrase ();

  if (mutt_get_password (_("Enter PGP passphrase:"), PgpPass, sizeof (PgpPass)) == 0)
  {
    PgpExptime = time (NULL) + PgpTimeout;
    return (1);
  }
  else
  {
    PgpExptime = 0;
    return (0);
  }
  /* not reached */
}

void mutt_forget_passphrase (void)
{
  pgp_void_passphrase ();
  mutt_message _("PGP passphrase forgotten.");
}


char *pgp_keyid(pgp_key_t *k)
{
  if((k->flags & KEYFLAG_SUBKEY) && k->parent)
    k = k->parent;

  return _pgp_keyid(k);
}

char *_pgp_keyid(pgp_key_t *k)
{
  if(option(OPTPGPLONGIDS))
    return k->keyid;
  else
    return (k->keyid + 8);
}

/* ----------------------------------------------------------------------------
 * Routines for handing PGP input.
 */

/* print the current time to avoid spoofing of the signature output */
static void pgp_current_time (STATE *s)
{
  time_t t;
  char p[STRING];

  t = time (NULL);
  setlocale (LC_TIME, "");
  strftime (p, sizeof (p),
	    _("[-- PGP output follows (current time: %c) --]\n"),
	    localtime (&t));
  setlocale (LC_TIME, "C");
  state_attach_puts (p, s);
}


/* Copy PGP output messages and look for signs of a good signature */

static int pgp_copy_checksig (FILE *fpin, FILE *fpout)
{
