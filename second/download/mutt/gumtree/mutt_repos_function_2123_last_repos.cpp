static void imap_add_folder (char delim, char *folder, int noselect,
  int noinferiors, struct browser_state *state, short isparent)
{
  char tmp[LONG_STRING];
  char relpath[LONG_STRING];
  IMAP_MBOX mx;
  BUFFY *b;

  if (imap_parse_path (state->folder, &mx))
    return;

  if (state->entrylen + 1 == state->entrymax)
  {
    safe_realloc (&state->entry,
      sizeof (struct folder_file) * (state->entrymax += 256));
    memset (state->entry + state->entrylen, 0,
      (sizeof (struct folder_file) * (state->entrymax - state->entrylen)));
  }

  /* render superiors as unix-standard ".." */
  if (isparent)
    strfcpy (relpath, "../", sizeof (relpath));
  /* strip current folder from target, to render a relative path */
  else if (!mutt_strncmp (mx.mbox, folder, mutt_strlen (mx.mbox)))
    strfcpy (relpath, folder + mutt_strlen (mx.mbox), sizeof (relpath));
  else
    strfcpy (relpath, folder, sizeof (relpath));

  /* apply filemask filter. This should really be done at menu setup rather
   * than at scan, since it's so expensive to scan. But that's big changes
   * to browser.c */
  if (!((regexec (Mask.rx, relpath, 0, NULL, 0) == 0) ^ Mask.not))
  {
    FREE (&mx.mbox);
    return;
  }

  imap_qualify_path (tmp, sizeof (tmp), &mx, folder);
  (state->entry)[state->entrylen].name = safe_strdup (tmp);

  /* mark desc with delim in browser if it can have subfolders */
  if (!isparent && !noinferiors && strlen (relpath) < sizeof (relpath) - 1)
  {
    relpath[strlen (relpath) + 1] = '\0';
    relpath[strlen (relpath)] = delim;
  }
  
  (state->entry)[state->entrylen].desc = safe_strdup (relpath);

  (state->entry)[state->entrylen].imap = 1;
  /* delimiter at the root is useless. */
  if (folder[0] == '\0')
    delim = '\0';
  (state->entry)[state->entrylen].delim = delim;
  (state->entry)[state->entrylen].selectable = !noselect;
  (state->entry)[state->entrylen].inferiors = !noinferiors;

  b = Incoming;
  while (b && mutt_strcmp (tmp, b->path))
    b = b->next;
  if (b)
  {
    if (Context &&
        !mutt_strcmp (b->realpath, Context->realpath))
    {
      b->msg_count = Context->msgcount;
      b->msg_unread = Context->unread;
    }
    (state->entry)[state->entrylen].has_buffy = 1;
    (state->entry)[state->entrylen].new = b->new;
    (state->entry)[state->entrylen].msg_count = b->msg_count;
    (state->entry)[state->entrylen].msg_unread = b->msg_unread;
  }

  (state->entrylen)++;

  FREE (&mx.mbox);
}