  size_t begin;
  int	 tabs;
} ENTER_STATE;

/* flags for the STATE struct */
#define M_DISPLAY	(1<<0) /* output is displayed to the user */
#define M_VERIFY	(1<<1) /* perform signature verification */
#define M_PENDINGPREFIX (1<<2) /* prefix to write, but character must follow */
#define M_WEED          (1<<3) /* weed headers even when not in display mode */
#define M_CHARCONV	(1<<4) /* Do character set conversions */
#define M_PRINTING	(1<<5) /* are we printing? - M_DISPLAY "light" */
#define M_REPLYING	(1<<6) /* are we replying? */
#define M_FIRSTDONE	(1<<7) /* the first attachment has been done */

#define state_set_prefix(s) ((s)->flags |= M_PENDINGPREFIX)
#define state_reset_prefix(s) ((s)->flags &= ~M_PENDINGPREFIX)
#define state_puts(x,y) fputs(x,(y)->fpout)
#define state_putc(x,y) fputc(x,(y)->fpout)

void state_mark_attach (STATE *);
void state_attach_puts (const char *, STATE *);
void state_prefix_putc (char, STATE *);
int  state_printf(STATE *, const char *, ...);
int state_putwc (wchar_t, STATE *);
int state_putws (const wchar_t *, STATE *);

/* for attachment counter */
typedef struct
{
  char   *major;
  int     major_int;
  char   *minor;
  regex_t minor_rx;
} ATTACH_MATCH;

#define M_PARTS_TOPLEVEL	(1<<0)	/* is the top-level part */

#include "ascii.h"
#include "protos.h"
#include "lib.h"
#include "globals.h"

#endif /*MUTT_H*/
