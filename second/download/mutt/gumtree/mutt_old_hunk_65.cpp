
  /* the offset stored in the header does not include the MMDF_SEP, so make
   * sure we seek to the correct location
   */
  if (ctx->magic == M_MMDF)
    offset -= (sizeof MMDF_SEP - 1);
  else if (ctx->magic == M_KENDRA)
    offset -= (sizeof KENDRA_SEP - 1);
  
  /* allocate space for the new offsets */
  newOffset = safe_calloc (ctx->msgcount - first, sizeof (struct m_update_t));
  oldOffset = safe_calloc (ctx->msgcount - first, sizeof (struct m_update_t));

  for (i = first, j = 0; i < ctx->msgcount; i++)
  {
    /*
     * back up some information which is needed to restore offsets when
     * something fails.
     */
    
    oldOffset[i-first].valid  = 1;
    oldOffset[i-first].hdr    = ctx->hdrs[i]->offset;
    oldOffset[i-first].body   = ctx->hdrs[i]->content->offset;
    oldOffset[i-first].lines  = ctx->hdrs[i]->lines;
    oldOffset[i-first].length = ctx->hdrs[i]->content->length;
    
    if (! ctx->hdrs[i]->deleted)
    {
      j++;
      if (!ctx->quiet && WriteInc && ((i % WriteInc) == 0 || j == 1))
	mutt_message (_("Writing messages... %d (%d%%)"), i,
		      ftell (ctx->fp) / (ctx->size / 100 + 1));

      if (ctx->magic == M_MMDF)
      {
	if (fputs (MMDF_SEP, fp) == EOF)
	{
	  mutt_perror (tempfile);
	  mutt_sleep (5);
	  unlink (tempfile);
	  goto bail;
	}
	  
      }
      else if (ctx->magic == M_KENDRA)
      {
	if (fputs (KENDRA_SEP, fp) == EOF)
	{
	  mutt_perror (tempfile);
	  mutt_sleep (5);
	  unlink (tempfile);
	  goto bail;
	}
      }

      /* save the new offset for this message.  we add `offset' because the
       * temporary file only contains saved message which are located after
       * `offset' in the real mailbox
       */
      newOffset[i - first].hdr = ftell (fp) + offset;

      if (mutt_copy_message (fp, ctx, ctx->hdrs[i], M_CM_UPDATE, CH_FROM | CH_UPDATE | CH_UPDATE_LEN) == -1)
      {
	mutt_perror (tempfile);
	mutt_sleep (5);
	unlink (tempfile);
	goto bail;
      }
