char* imap_set_flags (IMAP_DATA* idata, HEADER* h, char* s)
{
  CONTEXT* ctx = idata->ctx;
  IMAP_HEADER newh;
  unsigned char readonly;

  memset (&newh, 0, sizeof (newh));
  newh.data = safe_calloc (1, sizeof (IMAP_HEADER_DATA));

  dprint (2, (debugfile, "imap_fetch_message: parsing FLAGS\n"));
  if ((s = msg_parse_flags (&newh, s)) == NULL)
  {
    FREE (&newh.data);
    return NULL;
  }
  
  /* YAUH (yet another ugly hack): temporarily set context to
   * read-write even if it's read-only, so *server* updates of
   * flags can be processed by mutt_set_flag. ctx->changed must
   * be restored afterwards */
  readonly = ctx->readonly;
  ctx->readonly = 0;
	    
  mutt_set_flag (ctx, h, M_NEW, !(newh.read || newh.old));
  mutt_set_flag (ctx, h, M_OLD, newh.old);
  mutt_set_flag (ctx, h, M_READ, newh.read);
  mutt_set_flag (ctx, h, M_DELETE, newh.deleted);
  mutt_set_flag (ctx, h, M_FLAG, newh.flagged);
  mutt_set_flag (ctx, h, M_REPLIED, newh.replied);

  /* this message is now definitively *not* changed (mutt_set_flag
   * marks things changed as a side-effect) */
  h->changed = 0;
  ctx->changed &= ~readonly;
  ctx->readonly = readonly;

  mutt_free_list (&(HEADER_DATA(h)->keywords));
  HEADER_DATA(h)->keywords = newh.data->keywords;
  FREE(&newh.data);

  return s;
}