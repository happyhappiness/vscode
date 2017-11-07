static int edit_address_list (int line, ADDRESS **addr)
{
  char buf[HUGE_STRING] = ""; /* needs to be large for alias expansion */
  char *err = NULL;
  
  mutt_addrlist_to_local (*addr);
  rfc822_write_address (buf, sizeof (buf), *addr, 0);
  if (mutt_get_field (Prompts[line], buf, sizeof (buf), MUTT_ALIAS) == 0)
  {
    rfc822_free_address (addr);
    *addr = mutt_parse_adrlist (*addr, buf);
    *addr = mutt_expand_aliases (*addr);
  }

  if (option (OPTNEEDREDRAW))
  {
    unset_option (OPTNEEDREDRAW);
    return (REDRAW_FULL);
  }

  if (mutt_addrlist_to_intl (*addr, &err) != 0)
  {
    mutt_error (_("Warning: '%s' is a bad IDN."), err);
    mutt_refresh();
    FREE (&err);
  }

  /* redraw the expanded list so the user can see the result */
  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), *addr, 1);
  mutt_window_move (MuttIndexWindow, line, HDR_XOFFSET);
  mutt_paddstr (W, buf);
  
  return 0;
}