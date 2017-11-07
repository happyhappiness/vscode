static inline int mutt_term_width(short wrap)
{
  if (wrap < 0)
    return COLS > -wrap ? COLS + wrap : COLS;
  else if (wrap)
    return wrap < COLS ? wrap : COLS;
  else
    return COLS;
}