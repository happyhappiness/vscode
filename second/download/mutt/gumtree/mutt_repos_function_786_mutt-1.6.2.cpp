static void add_folder (MUTTMENU *m, struct browser_state *state,
			const char *name, const struct stat *s, unsigned int new)
{
  if (state->entrylen == state->entrymax)
  {
    /* need to allocate more space */
    safe_realloc (&state->entry,
		  sizeof (struct folder_file) * (state->entrymax += 256));
    memset (&state->entry[state->entrylen], 0,
	    sizeof (struct folder_file) * 256);
    if (m)
      m->data = state->entry;
  }

  if (s != NULL)
  {
    (state->entry)[state->entrylen].mode = s->st_mode;
    (state->entry)[state->entrylen].mtime = s->st_mtime;
    (state->entry)[state->entrylen].size = s->st_size;
    
    (state->entry)[state->entrylen].st = safe_malloc (sizeof (struct stat));
    memcpy ((state->entry)[state->entrylen].st, s, sizeof (struct stat));
  }

  (state->entry)[state->entrylen].new = new;
  (state->entry)[state->entrylen].name = safe_strdup (name);
  (state->entry)[state->entrylen].desc = safe_strdup (name);
#ifdef USE_IMAP
  (state->entry)[state->entrylen].imap = 0;
#endif
  (state->entrylen)++;
}