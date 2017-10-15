#endif

#ifdef HAVE_SYS_RESOURCE_H
# include <sys/resource.h>
#endif

#ifdef CRYPT_BACKEND_CLASSIC_PGP

#include "mutt_crypt.h"
#include "mutt_menu.h"


char PgpPass[LONG_STRING];
time_t PgpExptime = 0; /* when does the cached passphrase expire? */

void pgp_void_passphrase (void)
{
  memset (PgpPass, 0, sizeof (PgpPass));
  PgpExptime = 0;
}

int pgp_valid_passphrase (void)
{
  time_t now = time (NULL);

  if (pgp_use_gpg_agent())
    {
      *PgpPass = 0;
      return 1; /* handled by gpg-agent */
    }

  if (now < PgpExptime)
    /* Use cached copy.  */
    return 1;
  
  pgp_void_passphrase ();

  if (mutt_get_password (_("Enter PGP passphrase:"), PgpPass, sizeof (PgpPass)) == 0)
    {
      PgpExptime = time (NULL) + PgpTimeout;
      return (1);
    }
  else
    PgpExptime = 0;

  return 0;
}

void pgp_forget_passphrase (void)
{
  pgp_void_passphrase ();
  mutt_message _("PGP passphrase forgotten.");
}

int pgp_use_gpg_agent (void)
{
  char *tty;

  if (!option (OPTUSEGPGAGENT) || !getenv ("GPG_AGENT_INFO"))
    return 0;

  if ((tty = ttyname(0)))
    setenv("GPG_TTY", tty, 0);

  return 1;
}

char *pgp_keyid(pgp_key_t k)
{
  if((k->flags & KEYFLAG_SUBKEY) && k->parent && option(OPTPGPIGNORESUB))
    k = k->parent;

  return _pgp_keyid(k);
}

char *_pgp_keyid(pgp_key_t k)
{
  if(option(OPTPGPLONGIDS))
    return k->keyid;
  else
    return (k->keyid + 8);
}

/* ----------------------------------------------------------------------------
 * Routines for handing PGP input.
 */



/* Copy PGP output messages and look for signs of a good signature */

static int pgp_copy_checksig (FILE *fpin, FILE *fpout)
{
