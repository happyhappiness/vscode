      /* Since messages could have been deleted, the offsets stored in memory
       * will be wrong, so update what we can, which is the offset of this
       * message, and the offset of the body.  If this is a multipart message,
       * we just flush the in memory cache so that the message will be reparsed
       * if the user accesses it later.
       */
      newOffset[i - first].body = ftell (fp) - ctx->hdrs[i]->content->length + offset;
      mutt_free_body (&ctx->hdrs[i]->content->parts);

      switch(ctx->magic)
      {
	case M_MMDF: 
	  if(fputs(MMDF_SEP, fp) == EOF) 
