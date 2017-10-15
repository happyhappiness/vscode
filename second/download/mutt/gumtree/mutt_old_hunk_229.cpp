  size_t curpos;
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
