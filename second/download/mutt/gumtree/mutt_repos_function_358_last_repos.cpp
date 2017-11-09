void km_error_key (int menu)
{
  char buf[SHORT_STRING];
  struct keymap_t *key;
  int p, op;

  key = km_find_func (menu, OP_HELP);
  if (!key && (menu != MENU_EDITOR) && (menu != MENU_PAGER))
    key = km_find_func (MENU_GENERIC, OP_HELP);
  if (!key)
  {
    mutt_error _("Key is not bound.");
    return;
  }

  /* Make sure the key is really the help key in this menu.
   *
   * OP_END_COND is used as a barrier to ensure nothing extra
   * is left in the unget buffer.
   *
   * Note that km_expand_key() + tokenize_unget_string() should
   * not be used here: control sequences are expanded to a form
   * (e.g. "^H") not recognized by km_dokey(). */
  mutt_unget_event (0, OP_END_COND);
  p = key->len;
  while (p--)
    mutt_unget_event (key->keys[p], 0);

  /* Note, e.g. for the index menu:
   *   bind generic ?   noop
   *   bind generic ,a  help
   *   bind index   ,ab quit
   * The index keybinding shadows the generic binding.
   * OP_END_COND will be read and returned as the op.
   *
   *   bind generic ?   noop
   *   bind generic dq  help
   *   bind index   d   delete-message
   * OP_DELETE will be returned as the op, leaving "q" + OP_END_COND
   * in the unget buffer.
   */
  op = km_dokey (menu);
  if (op != OP_END_COND)
    mutt_flush_unget_to_endcond ();
  if (op != OP_HELP)
  {
    mutt_error _("Key is not bound.");
    return;
  }

  km_expand_key (buf, sizeof(buf), key);
  mutt_error (_("Key is not bound.  Press '%s' for help."), buf);
  return;
}