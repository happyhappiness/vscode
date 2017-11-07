static int edit_address_list (int line, ADDRESS **addr)
{
  char buf[HUGE_STRING] = ""; /* needs to be large for alias expansion */

  rfc822_write_address (buf, sizeof (buf), *addr);
  if (mutt_get_field (Prompts[line - 1], buf, sizeof (buf), M_ALIAS) == 0)
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

  /* redraw the expanded list so the user can see the result */
  buf[0] = 0;
  rfc822_write_address (buf, sizeof (buf), *addr);
  move (line, HDR_XOFFSET);
  mutt_paddstr (W, buf);

  return 0;
}