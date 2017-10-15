	    fprintf(fpout, "%s", AttachSep);
	    safe_fclose (&fpout);
	  }
	}
	else
	{
	  rc = mutt_save_attachment (fp, top, tfile, M_SAVE_APPEND, hdr);
	  if (rc == 0 && AttachSep && (fpout = fopen (tfile,"a")) != NULL)
	  {
	    fprintf(fpout, "%s", AttachSep);
	    safe_fclose (&fpout);
	  }
	}
