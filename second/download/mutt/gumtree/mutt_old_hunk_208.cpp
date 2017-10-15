
int mutt_change_flag (HEADER *h, int bf)
{
  int i, flag;
  event_t event;

  mvprintw (LINES - 1, 0, "%s? (D/N/O/r/*/!): ", bf ? _("Set flag") : _("Clear flag"));
  clrtoeol ();

  event = mutt_getch();
  i = event.ch;
  if (i < 0)
  {
    CLEARLINE (LINES-1);
    return (-1);
  }

  CLEARLINE (LINES-1);

  switch (i)
  {
    case 'd':
    case 'D':
      flag = M_DELETE;
      break;

    case 'N':
    case 'n':
      flag = M_NEW;
      break;

    case 'o':
    case 'O':
      if (h)
	mutt_set_flag (Context, h, M_READ, !bf);
      else
	mutt_tag_set_flag (M_READ, !bf);
      flag = M_OLD;
      break;

    case 'r':
    case 'R':
      flag = M_REPLIED;
      break;

    case '*':
      flag = M_TAG;
      break;

    case '!':
      flag = M_FLAG;
      break;

    default:
      BEEP ();
      return (-1);
  }
