void mutt_help (int menu)
{
  char t[_POSIX_PATH_MAX];
  char buf[SHORT_STRING];
  char *desc;
  FILE *f;
  struct binding_t *funcs;

  mutt_mktemp (t);

  funcs = km_get_table (menu);
  desc = mutt_getnamebyvalue (menu, Menus);
  if (!desc)
    desc = _("<UNKNOWN>");
  
  do {
    if ((f = safe_fopen (t, "w")) == NULL)
    {
      mutt_perror (t);
      return;
    }
  
    dump_menu (f, menu);
    if (menu != MENU_EDITOR && menu != MENU_PAGER)
    {
      fputs (_("\nGeneric bindings:\n\n"), f);
      dump_menu (f, MENU_GENERIC);
    }
  
    fputs (_("\nUnbound functions:\n\n"), f);
    if (funcs)
      dump_unbound (f, funcs, Keymaps[menu], NULL);
    if (menu != MENU_PAGER)
      dump_unbound (f, OpGeneric, Keymaps[MENU_GENERIC], Keymaps[menu]);
  
    fclose (f);
  
    snprintf (buf, sizeof (buf), _("Help for %s"), desc);
  }
  while
    (mutt_do_pager (buf, t,
		    M_PAGER_RETWINCH | M_PAGER_MARKER | M_PAGER_NSKIP,
		    NULL)
     == OP_REFORMAT_WINCH);
}