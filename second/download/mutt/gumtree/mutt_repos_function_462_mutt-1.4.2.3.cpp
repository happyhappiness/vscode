static void redraw_pgp_lines (int pgp)
{
  mvaddstr (HDR_PGP, 0,     "     PGP: ");
  if ((pgp & (PGPENCRYPT | PGPSIGN)) == (PGPENCRYPT | PGPSIGN))
    addstr (_("Sign, Encrypt"));
  else if (pgp & PGPENCRYPT)
    addstr (_("Encrypt"));
  else if (pgp & PGPSIGN)
    addstr (_("Sign"));
  else
    addstr (_("Clear"));
  clrtoeol ();

  move (HDR_PGPSIGINFO, 0);
  clrtoeol ();
  if (pgp & PGPSIGN)
    printw ("%s%s", _(" sign as: "), PgpSignAs ? PgpSignAs : _("<default>"));
}