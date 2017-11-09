char* imap_set_flags (IMAP_DATA* idata, HEADER* h, char* s)
{
  CONTEXT* ctx = idata->ctx;
  IMAP_HEADER newh;
  IMAP_HEADER_DATA* hd;
  unsigned char readonly;

  memset (&newh, 0, sizeof (newh));
  hd = h->data;
  newh.data = hd;

  dprint (2, (debugfile, "imap_set_flags: parsing FLAGS\n"));
  if ((s = msg_parse_flags (&newh, s)) == NULL)
    return NULL;

  /* YAUH (yet another ugly hack): temporarily set context to
   * read-write even if it's read-only, so *server* updates of
   * flags can be processed by mutt_set_flag. ctx->changed must
   * be restored afterwards */
  readonly = ctx->readonly;
  ctx->readonly = 0;

  mutt_set_flag (ctx, h, MUTT_NEW, !(hd->read || hd->old));
  mutt_set_flag (ctx, h, MUTT_OLD, hd->old);
  mutt_set_flag (ctx, h, MUTT_READ, hd->read);
  mutt_set_flag (ctx, h, MUTT_DELETE, hd->deleted);
  mutt_set_flag (ctx, h, MUTT_FLAG, hd->flagged);
  mutt_set_flag (ctx, h, MUTT_REPLIED, hd->replied);

  /* this message is now definitively *not* changed (mutt_set_flag
   * marks things changed as a side-effect) */
  h->changed = 0;
  ctx->changed &= ~readonly;
  ctx->readonly = readonly;

  return s;
}