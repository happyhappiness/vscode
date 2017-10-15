
	if ((fout = safe_fopen (tempfile, "w")) == NULL)
	{
	  if (!option (OPTNOCURSES))
	    mutt_endwin (NULL);
	  perror (tempfile);
	  safe_fclose (&fin);
	  FREE (&tempfile);
	  exit (1);
	}
	if (fin)
	  mutt_copy_stream (fin, fout);
	else if (bodytext)
	  fputs (bodytext, fout);
	safe_fclose (&fout);
	if (fin && fin != stdin)
	  safe_fclose (&fin);
      }
    }

    FREE (&bodytext);
    
    if (attach)
    {
      LIST *t = attach;
      BODY *a = NULL;

