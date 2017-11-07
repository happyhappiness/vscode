static int retry_generic (int menu, keycode_t *keys, int keyslen, int lastkey)
{
  if (menu != MENU_EDITOR && menu != MENU_GENERIC && menu != MENU_PAGER)
  {
    if (lastkey)
      mutt_ungetch (lastkey, 0);
    for (; keyslen; keyslen--)
      mutt_ungetch (keys[keyslen - 1], 0);
    return (km_dokey (MENU_GENERIC));
  }
  if (menu != MENU_EDITOR)
  {
    /* probably a good idea to flush input here so we can abort macros */
    mutt_flushinp ();
  }
  return OP_NULL;
}