int mutt_change_flag (HEADER *h, int bf)
{
  int i, flag;
  event_t event;

  mutt_window_mvprintw (MuttMessageWindow, 0, 0,
                        "%s? (D/N/O/r/*/!): ", bf ? _("Set flag") : _("Clear flag"));
  mutt_window_clrtoeol (MuttMessageWindow);

  event = mutt_getch();
  i = event.ch;
  if (i < 0)
  {
    mutt_window_clearline (MuttMessageWindow, 0);
    return (-1);
  }

  mutt_window_clearline (MuttMessageWindow, 0);

  switch (i)
  {
    case 'd':
    case 'D':
      if (!bf)
      {
        if (h)
          mutt_set_flag (Context, h, MUTT_PURGE, bf);
        else
          mutt_tag_set_flag (MUTT_PURGE, bf);
      }
      flag = MUTT_DELETE;
      break;

    case 'N':
    case 'n':
      flag = MUTT_NEW;
      break;

    case 'o':
    case 'O':
      if (h)
	mutt_set_flag (Context, h, MUTT_READ, !bf);
      else
	mutt_tag_set_flag (MUTT_READ, !bf);
      flag = MUTT_OLD;
      break;

    case 'r':
    case 'R':
      flag = MUTT_REPLIED;
      break;

    case '*':
      flag = MUTT_TAG;
      break;

    case '!':
      flag = MUTT_FLAG;
      break;

    default:
      BEEP ();
      return (-1);
  }

  if (h)
    mutt_set_flag (Context, h, flag, bf);
  else
    mutt_tag_set_flag (flag, bf);

  return 0;
}