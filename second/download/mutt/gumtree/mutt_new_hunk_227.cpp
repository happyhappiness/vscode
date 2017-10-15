       */
      newOffset[i - first].body = ftello (fp) - ctx->hdrs[i]->content->length + offset;
      mutt_free_body (&ctx->hdrs[i]->content->parts);

      switch(ctx->magic)
      {
	case MUTT_MMDF: 
	  if(fputs(MMDF_SEP, fp) == EOF) 
	  {
	    mutt_perror (tempfile);
	    mutt_sleep (5);
	    unlink (tempfile);
	    goto bail; 
