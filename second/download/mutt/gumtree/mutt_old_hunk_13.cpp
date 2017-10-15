  HDR_FCC,

#ifdef MIXMASTER
  HDR_MIX,
#endif

#ifdef HAVE_PGP
  HDR_PGP,
  HDR_PGPSIGINFO,
#endif
  

  HDR_ATTACH  = (HDR_FCC + 5) /* where to start printing the attachments */
};

#define HDR_XOFFSET 10
#define TITLE_FMT "%10s" /* Used for Prompts, which are ASCII */
#define W (COLS - HDR_XOFFSET)

static char *Prompts[] =
{
  "From: ",
  "To: ",
  "Cc: ",
  "Bcc: ",
  "Subject: ",
  "Reply-To: ",
  "Fcc: "
};

static struct mapping_t ComposeHelp[] = {
  { N_("Send"),    OP_COMPOSE_SEND_MESSAGE },
  { N_("Abort"),   OP_EXIT },
  { "To",      OP_COMPOSE_EDIT_TO },
  { "CC",      OP_COMPOSE_EDIT_CC },
  { "Subj",    OP_COMPOSE_EDIT_SUBJECT },
  { N_("Attach file"),  OP_COMPOSE_ATTACH_FILE },
  { N_("Descrip"), OP_COMPOSE_EDIT_DESCRIPTION },
  { N_("Help"),    OP_HELP },
  { NULL }
};

static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
    mutt_FormatString (b, blen, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(((ATTACHPTR **) menu->data)[num]),
	    M_FORMAT_STAT_FILE | M_FORMAT_ARROWCURSOR);
}



#ifdef HAVE_PGP
#include "pgp.h"

static void redraw_pgp_lines (int pgp)
{
  mvaddstr (HDR_PGP, 0,     "     PGP: ");
  if ((pgp & (PGPENCRYPT | PGPSIGN)) == (PGPENCRYPT | PGPSIGN))
    addstr (_("Sign, Encrypt"));
  else if (pgp & PGPENCRYPT)
    addstr (_("Encrypt"));
  else if (pgp & PGPSIGN)
    addstr (_("Sign"));
  else
    addstr (_("Clear"));
  clrtoeol ();

  move (HDR_PGPSIGINFO, 0);
  clrtoeol ();
  if (pgp & PGPSIGN)
    printw ("%s%s", _(" sign as: "), PgpSignAs ? PgpSignAs : _("<default>"));
}

static int pgp_send_menu (int bits, int *redraw)
{
  pgp_key_t *p;
  char input_signas[SHORT_STRING];

  switch (mutt_multi_choice (_("(e)ncrypt, (s)ign, sign (a)s, (b)oth, or (f)orget it? "),
			     _("esabf")))
  {
  case 1: /* (e)ncrypt */
    bits |= PGPENCRYPT;
    break;

  case 2: /* (s)ign */
    bits |= PGPSIGN;
    break;

  case 3: /* sign (a)s */

    unset_option(OPTPGPCHECKTRUST);

    if ((p = pgp_ask_for_key (_("Sign as: "), NULL, KEYFLAG_CANSIGN, PGP_SECRING)))
    {
      snprintf (input_signas, sizeof (input_signas), "0x%s", pgp_keyid (p));
      mutt_str_replace (&PgpSignAs, input_signas);
      pgp_free_key (&p);
      
      bits |= PGPSIGN;
	
      pgp_void_passphrase ();	/* probably need a different passphrase */
    }
    else
    {
      bits &= ~PGPSIGN;
    }

    *redraw = REDRAW_FULL;
    break;

  case 4: /* (b)oth */
    bits = PGPENCRYPT | PGPSIGN;
    break;

  case 5: /* (f)orget it */
    bits = 0;
    break;
  }
  if (!*redraw)
    redraw_pgp_lines (bits);
  return (bits);
}
#endif /* HAVE_PGP */

#ifdef MIXMASTER

static void redraw_mix_line (LIST *chain)
{
  int c;
