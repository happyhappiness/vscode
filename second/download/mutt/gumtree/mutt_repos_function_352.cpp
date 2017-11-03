void km_init (void)
{
  memset (Keymaps, 0, sizeof (struct keymap_t *) * MENU_MAX);

  create_bindings (OpAttach, MENU_ATTACH);
  create_bindings (OpBrowser, MENU_FOLDER);
  create_bindings (OpCompose, MENU_COMPOSE);
  create_bindings (OpMain, MENU_MAIN);
  create_bindings (OpPager, MENU_PAGER);
  create_bindings (OpPost, MENU_POST);
  create_bindings (OpQuery, MENU_QUERY);
  create_bindings (OpAlias, MENU_ALIAS);


  if ((WithCrypto & APPLICATION_PGP))
    create_bindings (OpPgp, MENU_PGP);

  if ((WithCrypto & APPLICATION_SMIME))
    create_bindings (OpSmime, MENU_SMIME);

#ifdef CRYPT_BACKEND_GPGME
  create_bindings (OpPgp, MENU_KEY_SELECT_PGP);
  create_bindings (OpSmime, MENU_KEY_SELECT_SMIME);
#endif

#ifdef MIXMASTER
  create_bindings (OpMix, MENU_MIX);
  
  km_bindkey ("<space>", MENU_MIX, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("h", MENU_MIX, OP_MIX_CHAIN_PREV);
  km_bindkey ("l", MENU_MIX, OP_MIX_CHAIN_NEXT);
#endif
  
  /* bindings for the line editor */
  create_bindings (OpEditor, MENU_EDITOR);
  
  km_bindkey ("<up>", MENU_EDITOR, OP_EDITOR_HISTORY_UP);
  km_bindkey ("<down>", MENU_EDITOR, OP_EDITOR_HISTORY_DOWN);
  km_bindkey ("<left>", MENU_EDITOR, OP_EDITOR_BACKWARD_CHAR);
  km_bindkey ("<right>", MENU_EDITOR, OP_EDITOR_FORWARD_CHAR);
  km_bindkey ("<home>", MENU_EDITOR, OP_EDITOR_BOL);
  km_bindkey ("<end>", MENU_EDITOR, OP_EDITOR_EOL);
  km_bindkey ("<backspace>", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  km_bindkey ("<delete>", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  km_bindkey ("\177", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  
  /* generic menu keymap */
  create_bindings (OpGeneric, MENU_GENERIC);
  
  km_bindkey ("<home>", MENU_GENERIC, OP_FIRST_ENTRY);
  km_bindkey ("<end>", MENU_GENERIC, OP_LAST_ENTRY);
  km_bindkey ("<pagedown>", MENU_GENERIC, OP_NEXT_PAGE);
  km_bindkey ("<pageup>", MENU_GENERIC, OP_PREV_PAGE);
  km_bindkey ("<right>", MENU_GENERIC, OP_NEXT_PAGE);
  km_bindkey ("<left>", MENU_GENERIC, OP_PREV_PAGE);
  km_bindkey ("<up>", MENU_GENERIC, OP_PREV_ENTRY);
  km_bindkey ("<down>", MENU_GENERIC, OP_NEXT_ENTRY);
  km_bindkey ("1", MENU_GENERIC, OP_JUMP);
  km_bindkey ("2", MENU_GENERIC, OP_JUMP);
  km_bindkey ("3", MENU_GENERIC, OP_JUMP);
  km_bindkey ("4", MENU_GENERIC, OP_JUMP);
  km_bindkey ("5", MENU_GENERIC, OP_JUMP);
  km_bindkey ("6", MENU_GENERIC, OP_JUMP);
  km_bindkey ("7", MENU_GENERIC, OP_JUMP);
  km_bindkey ("8", MENU_GENERIC, OP_JUMP);
  km_bindkey ("9", MENU_GENERIC, OP_JUMP);

  km_bindkey ("<enter>", MENU_GENERIC, OP_GENERIC_SELECT_ENTRY);

  /* Miscellaneous extra bindings */
  
  km_bindkey (" ", MENU_MAIN, OP_DISPLAY_MESSAGE);
  km_bindkey ("<up>", MENU_MAIN, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<down>", MENU_MAIN, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("J", MENU_MAIN, OP_NEXT_ENTRY);
  km_bindkey ("K", MENU_MAIN, OP_PREV_ENTRY);
  km_bindkey ("x", MENU_MAIN, OP_EXIT);

  km_bindkey ("<enter>", MENU_MAIN, OP_DISPLAY_MESSAGE);

  km_bindkey ("x", MENU_PAGER, OP_EXIT);
  km_bindkey ("i", MENU_PAGER, OP_EXIT);
  km_bindkey ("<backspace>", MENU_PAGER, OP_PREV_LINE);
  km_bindkey ("<pagedown>", MENU_PAGER, OP_NEXT_PAGE);
  km_bindkey ("<pageup>", MENU_PAGER, OP_PREV_PAGE);
  km_bindkey ("<up>", MENU_PAGER, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<right>", MENU_PAGER, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("<down>", MENU_PAGER, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("<left>", MENU_PAGER, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<home>", MENU_PAGER, OP_PAGER_TOP);
  km_bindkey ("<end>", MENU_PAGER, OP_PAGER_BOTTOM);
  km_bindkey ("1", MENU_PAGER, OP_JUMP);
  km_bindkey ("2", MENU_PAGER, OP_JUMP);
  km_bindkey ("3", MENU_PAGER, OP_JUMP);
  km_bindkey ("4", MENU_PAGER, OP_JUMP);
  km_bindkey ("5", MENU_PAGER, OP_JUMP);
  km_bindkey ("6", MENU_PAGER, OP_JUMP);
  km_bindkey ("7", MENU_PAGER, OP_JUMP);
  km_bindkey ("8", MENU_PAGER, OP_JUMP);
  km_bindkey ("9", MENU_PAGER, OP_JUMP);

  km_bindkey ("<enter>", MENU_PAGER, OP_NEXT_LINE);
  
  km_bindkey ("<return>", MENU_ALIAS, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("<enter>",  MENU_ALIAS, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("<space>", MENU_ALIAS, OP_TAG);

  km_bindkey ("<enter>", MENU_ATTACH, OP_VIEW_ATTACH);
  km_bindkey ("<enter>", MENU_COMPOSE, OP_VIEW_ATTACH);

  /* edit-to (default "t") hides generic tag-entry in Compose menu
     This will bind tag-entry to  "T" in the Compose menu */
  km_bindkey ("T", MENU_COMPOSE, OP_TAG);
}