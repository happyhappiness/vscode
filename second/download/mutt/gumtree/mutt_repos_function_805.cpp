static void add_folder (MUTTMENU *m, struct browser_state *state,
			const char *name, const struct stat *s, BUFFY *b)
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
    (state->entry)[state->entrylen].gid = s->st_gid;
    (state->entry)[state->entrylen].uid = s->st_uid;
    (state->entry)[state->entrylen].nlink = s->st_nlink;
    
    (state->entry)[state->entrylen].local = 1;
  }

  if (b)
  {
    (state->entry)[state->entrylen].has_buffy = 1;
    (state->entry)[state->entrylen].new = b->new;
    (state->entry)[state->entrylen].msg_count = b->msg_count;
    (state->entry)[state->entrylen].msg_unread = b->msg_unread;
  }

  (state->entry)[state->entrylen].name = safe_strdup (name);
  (state->entry)[state->entrylen].desc = safe_strdup (name);
#ifdef USE_IMAP
  (state->entry)[state->entrylen].imap = 0;
#endif
  (state->entrylen)++;
}