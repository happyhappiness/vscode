static void destroy_state (struct browser_state *state)
{
  int c;

  for (c = 0; c < state->entrylen; c++)
  {
    safe_free ((void **) &((state->entry)[c].name));
    safe_free ((void **) &((state->entry)[c].desc));
    safe_free ((void **) &((state->entry)[c].st));
  }
#ifdef USE_IMAP
  safe_free ((void **) &state->folder);
#endif
  safe_free ((void **) &state->entry);
}