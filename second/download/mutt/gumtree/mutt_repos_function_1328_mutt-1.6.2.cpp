static int menu_dialog_dokey (MUTTMENU *menu, int *ip)
{
  event_t ch;
  char *p;

  ch = mutt_getch ();

  if (ch.ch < 0)
  {
    *ip = -1;
    return 0;
  }

  if (ch.ch && (p = strchr (menu->keys, ch.ch)))
  {
    *ip = OP_MAX + (p - menu->keys + 1);
    return 0;
  }
  else
  {
    mutt_unget_event (ch.op ? 0 : ch.ch, ch.op ? ch.op : 0);
    return -1;
  }
}