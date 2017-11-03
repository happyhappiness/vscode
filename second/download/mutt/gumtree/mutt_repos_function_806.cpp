static void init_state (struct browser_state *state, MUTTMENU *menu)
{
  state->entrylen = 0;
  state->entrymax = 256;
  state->entry = (struct folder_file *) safe_calloc (state->entrymax, sizeof (struct folder_file));
#ifdef USE_IMAP
  state->imap_browse = 0;
#endif
  if (menu)
    menu->data = state->entry;
}