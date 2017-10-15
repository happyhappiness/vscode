  { N_("Help"),    OP_HELP },
  { NULL,	0 }
};

static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
    mutt_FormatString (b, blen, 0, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(((ATTACHPTR **) menu->data)[num]),
	    M_FORMAT_STAT_FILE | M_FORMAT_ARROWCURSOR);
}



#include "mutt_crypt.h"

static void redraw_crypt_lines (HEADER *msg)
{
  mvaddstr (HDR_CRYPT, 0, "Security: ");

  if ((WithCrypto & (APPLICATION_PGP | APPLICATION_SMIME)) == 0)
  {
    addstr(_("Not supported"));
    return;
  }
