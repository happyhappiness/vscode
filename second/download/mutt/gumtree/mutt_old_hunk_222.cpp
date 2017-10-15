 * to the user.
 */
void mutt_what_key (void)
{
  int ch;

  mvprintw(LINES-1,0, _("Enter keys (^G to abort): "));
  do {
    ch = getch();
    if (ch != ERR && ch != ctrl ('G'))
    {
      mutt_message(_("Char = %s, Octal = %o, Decimal = %d"),
	       km_keyname(ch), ch, ch);
