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
