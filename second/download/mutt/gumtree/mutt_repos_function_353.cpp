void km_error_key (int menu)
{
  char buf[SHORT_STRING];
  struct keymap_t *key;

  if(!(key = km_find_func(menu, OP_HELP)))
    key = km_find_func(MENU_GENERIC, OP_HELP);
  
  if(!(km_expand_key(buf, sizeof(buf), key)))
  {
    mutt_error _("Key is not bound.");
    return;
  }

  /* make sure the key is really the help key in this menu */
  tokenize_unget_string (buf);
  if (km_dokey (menu) != OP_HELP)
  {
    mutt_error _("Key is not bound.");
    return;
  }

  mutt_error (_("Key is not bound.  Press '%s' for help."), buf);
  return;
}