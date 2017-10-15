  HDR_CRYPT,
  HDR_CRYPTINFO,

  HDR_ATTACH  = (HDR_FCC + 5) /* where to start printing the attachments */
};

#define HDR_XOFFSET 10
#define TITLE_FMT "%10s" /* Used for Prompts, which are ASCII */
#define W (MuttIndexWindow->cols - HDR_XOFFSET)

static const char * const Prompts[] =
{
  "From: ",
  "To: ",
  "Cc: ",
  "Bcc: ",
  "Subject: ",
  "Reply-To: ",
  "Fcc: "
};

static const struct mapping_t ComposeHelp[] = {
  { N_("Send"),    OP_COMPOSE_SEND_MESSAGE },
  { N_("Abort"),   OP_EXIT },
  { "To",      OP_COMPOSE_EDIT_TO },
  { "CC",      OP_COMPOSE_EDIT_CC },
  { "Subj",    OP_COMPOSE_EDIT_SUBJECT },
  { N_("Attach file"),  OP_COMPOSE_ATTACH_FILE },
  { N_("Descrip"), OP_COMPOSE_EDIT_DESCRIPTION },
  { N_("Help"),    OP_HELP },
  { NULL,	0 }
};

static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
  mutt_FormatString (b, blen, 0, MuttIndexWindow->cols, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(((ATTACHPTR **) menu->data)[num]),
	    MUTT_FORMAT_STAT_FILE | MUTT_FORMAT_ARROWCURSOR);
}



#include "mutt_crypt.h"

static void redraw_crypt_lines (HEADER *msg)
{
  mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPT, 0, TITLE_FMT, "Security: ");

  if ((WithCrypto & (APPLICATION_PGP | APPLICATION_SMIME)) == 0)
  {
    addstr(_("Not supported"));
    return;
  }

  if ((msg->security & (ENCRYPT | SIGN)) == (ENCRYPT | SIGN))
    addstr (_("Sign, Encrypt"));
  else if (msg->security & ENCRYPT)
    addstr (_("Encrypt"));
  else if (msg->security & SIGN)
    addstr (_("Sign"));
  else
    addstr (_("None"));

  if ((msg->security & (ENCRYPT | SIGN)))
  {
    if ((WithCrypto & APPLICATION_PGP) && (msg->security & APPLICATION_PGP))
    {
      if ((msg->security & INLINE))
