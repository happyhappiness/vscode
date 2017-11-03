static inline int mutt_window_wrap_cols(mutt_window_t *win, short wrap)
{
  if (wrap < 0)
    return win->cols > -wrap ? win->cols + wrap : win->cols;
  else if (wrap)
    return wrap < win->cols ? wrap : win->cols;
  else
    return win->cols;
}