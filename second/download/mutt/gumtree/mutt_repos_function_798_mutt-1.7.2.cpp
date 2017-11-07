static void destroy_state (struct browser_state *state)
{
  int c;

  for (c = 0; c < state->entrylen; c++)
  {
    FREE (&((state->entry)[c].name));
    FREE (&((state->entry)[c].desc));
  }
#ifdef USE_IMAP
  FREE (&state->folder);
#endif
  FREE (&state->entry);
}