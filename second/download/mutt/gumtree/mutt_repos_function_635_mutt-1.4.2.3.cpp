static void flowed_stuff (STATE *s, char *cont, int level)
{
  if (!option (OPTTEXTFLOWED) && !(s->flags & M_DISPLAY))
    return;

  if (s->flags & M_DISPLAY)
  {
    /* 
     * Hack: If we are in the beginning of the line and there is 
     * some text on the line which looks like it's quoted, turn off 
     * ANSI colors, so quote coloring doesn't affect this line. 
     */
    if (*cont && !level && !mutt_strcmp (Pager, "builtin") && flowed_maybe_quoted (cont))
      state_puts ("\033[0m",s);
  }
  else if ((*cont == ' ') || (*cont == '>') || (!level && !mutt_strncmp (cont, "From ", 5)))
    state_putc (' ', s);
}