			 long size);
/* If percent is positive, it is displayed as percentage, otherwise
 * percentage is calculated from progress->size and pos if progress
 * was initialized with positive size, otherwise no percentage is shown */
void mutt_progress_update (progress_t* progress, long pos, int percent);

static inline int mutt_term_width(short wrap)
{
  if (wrap < 0)
    return COLS > -wrap ? COLS + wrap : COLS;
  else if (wrap)
    return wrap < COLS ? wrap : COLS;
  else
    return COLS;
}

extern int *ColorQuote;
extern int ColorQuoteUsed;
extern int ColorDefs[];
extern COLOR_LINE *ColorHdrList;
