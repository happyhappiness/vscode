    fputs (_("\nUnbound functions:\n\n"), f);
    if (funcs)
      dump_unbound (f, funcs, Keymaps[menu], NULL);
    if (menu != MENU_PAGER)
      dump_unbound (f, OpGeneric, Keymaps[MENU_GENERIC], Keymaps[menu]);
  
    safe_fclose (&f);
  
    snprintf (buf, sizeof (buf), _("Help for %s"), desc);
  }
  while
    (mutt_do_pager (buf, t,
		    M_PAGER_RETWINCH | M_PAGER_MARKER | M_PAGER_NSKIP | M_PAGER_NOWRAP,
		    NULL)
     == OP_REFORMAT_WINCH);
}
