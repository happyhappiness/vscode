  HDR_CRYPT,
  HDR_CRYPTINFO,

  HDR_ATTACH  = (HDR_FCC + 5) /* where to start printing the attachments */
};

int HeaderPadding[HDR_CRYPTINFO + 1] = {0};
int MaxHeaderWidth = 0;

#define HDR_XOFFSET MaxHeaderWidth
#define W (MuttIndexWindow->cols - MaxHeaderWidth)

static const char * const Prompts[] =
{
  /* L10N: Compose menu field.  May not want to translate. */
  N_("From: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("To: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("Cc: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("Bcc: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("Subject: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("Reply-To: "),
  /* L10N: Compose menu field.  May not want to translate. */
  N_("Fcc: "),
#ifdef MIXMASTER
  /* L10N: "Mix" refers to the MixMaster chain for anonymous email */
  N_("Mix: "),
#endif
  /* L10N: Compose menu field.  Holds "Encrypt", "Sign" related information */
  N_("Security: "),
  /* L10N:
   * This string is used by the compose menu.
   * Since it is hidden by default, it does not increase the
   * indentation of other compose menu fields.  However, if possible,
   * it should not be longer than the other compose menu fields.
   *
   * Since it shares the row with "Encrypt with:", it should not be longer
   * than 15-20 character cells.
   */
  N_("Sign as: ")
};

static const struct mapping_t ComposeHelp[] = {
  { N_("Send"),    OP_COMPOSE_SEND_MESSAGE },
  { N_("Abort"),   OP_EXIT },
  /* L10N: compose menu help line entry */
  { N_("To"),      OP_COMPOSE_EDIT_TO },
  /* L10N: compose menu help line entry */
  { N_("CC"),      OP_COMPOSE_EDIT_CC },
  /* L10N: compose menu help line entry */
  { N_("Subj"),    OP_COMPOSE_EDIT_SUBJECT },
  { N_("Attach file"),  OP_COMPOSE_ATTACH_FILE },
  { N_("Descrip"), OP_COMPOSE_EDIT_DESCRIPTION },
  { N_("Help"),    OP_HELP },
  { NULL,	0 }
};

static void calc_header_width_padding (int idx, const char *header, int calc_max)
{
  int width;

  HeaderPadding[idx] = mutt_strlen (header);
  width = mutt_strwidth (header);
  if (calc_max && MaxHeaderWidth < width)
    MaxHeaderWidth = width;
  HeaderPadding[idx] -= width;
}


/* The padding needed for each header is strlen() + max_width - strwidth().
 *
 * calc_header_width_padding sets each entry in HeaderPadding to
 * strlen - width.  Then, afterwards, we go through and add max_width
 * to each entry.
 */
static void init_header_padding (void)
{
  static short done = 0;
  int i;

  if (done)
    return;
  done = 1;

  for (i = 0; i <= HDR_CRYPT; i++)
    calc_header_width_padding (i, _(Prompts[i]), 1);

  /* Don't include "Sign as: " in the MaxHeaderWidth calculation.  It
   * doesn't show up by default, and so can make the indentation of
   * the other fields look funny. */
  calc_header_width_padding (HDR_CRYPTINFO, _(Prompts[HDR_CRYPTINFO]), 0);

  for (i = 0; i <= HDR_CRYPTINFO; i++)
  {
    HeaderPadding[i] += MaxHeaderWidth;
    if (HeaderPadding[i] < 0)
      HeaderPadding[i] = 0;
  }
}

static void snd_entry (char *b, size_t blen, MUTTMENU *menu, int num)
{
  ATTACH_CONTEXT *actx = (ATTACH_CONTEXT *)menu->data;

  mutt_FormatString (b, blen, 0, MuttIndexWindow->cols, NONULL (AttachFormat), mutt_attach_fmt,
	    (unsigned long)(actx->idx[actx->v2r[num]]),
	    MUTT_FORMAT_STAT_FILE | MUTT_FORMAT_ARROWCURSOR);
}



#include "mutt_crypt.h"

static void redraw_crypt_lines (HEADER *msg)
{
  SETCOLOR (MT_COLOR_COMPOSE_HEADER);
  mutt_window_mvprintw (MuttIndexWindow, HDR_CRYPT, 0,
                        "%*s", HeaderPadding[HDR_CRYPT], _(Prompts[HDR_CRYPT]));
  NORMAL_COLOR;

  if ((WithCrypto & (APPLICATION_PGP | APPLICATION_SMIME)) == 0)
  {
    addstr(_("Not supported"));
    return;
  }

  if ((msg->security & (ENCRYPT | SIGN)) == (ENCRYPT | SIGN))
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_BOTH);
    addstr (_("Sign, Encrypt"));
  }
  else if (msg->security & ENCRYPT)
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_ENCRYPT);
    addstr (_("Encrypt"));
  }
  else if (msg->security & SIGN)
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_SIGN);
    addstr (_("Sign"));
  }
  else
  {
    SETCOLOR (MT_COLOR_COMPOSE_SECURITY_NONE);
    addstr (_("None"));
  }
  NORMAL_COLOR;

  if ((msg->security & (ENCRYPT | SIGN)))
  {
    if ((WithCrypto & APPLICATION_PGP) && (msg->security & APPLICATION_PGP))
    {
      if ((msg->security & INLINE))
