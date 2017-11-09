int mutt_pipe_attachment (FILE *fp, BODY *b, const char *path, char *outfile)
{
  pid_t thepid;
  int out = -1;
  int rv = 0;
  
  if (outfile && *outfile)
    if ((out = safe_open (outfile, O_CREAT | O_EXCL | O_WRONLY)) < 0)
    {
      mutt_perror ("open");
      return 0;
    }

  mutt_endwin (NULL);

  if (fp)
  {
    /* recv case */

    STATE s;

    memset (&s, 0, sizeof (STATE));
    /* perform charset conversion on text attachments when piping */
    s.flags = MUTT_CHARCONV;

    if (outfile && *outfile)
      thepid = mutt_create_filter_fd (path, &s.fpout, NULL, NULL, -1, out, -1);
    else
      thepid = mutt_create_filter (path, &s.fpout, NULL, NULL);

    if (thepid < 0)
    {
      mutt_perror _("Can't create filter");
      goto bail;
    }
    
    s.fpin = fp;
    mutt_decode_attachment (b, &s);
    safe_fclose (&s.fpout);
  }
  else
  {
    /* send case */

    FILE *ifp, *ofp;

    if ((ifp = fopen (b->filename, "r")) == NULL)
    {
      mutt_perror ("fopen");
      if (outfile && *outfile)
      {
	close (out);
	unlink (outfile);
      }
      return 0;
    }

    if (outfile && *outfile)
      thepid = mutt_create_filter_fd (path, &ofp, NULL, NULL, -1, out, -1);
    else
      thepid = mutt_create_filter (path, &ofp, NULL, NULL);

    if (thepid < 0)
    {
      mutt_perror _("Can't create filter");
      safe_fclose (&ifp);
      goto bail;
    }
    
    mutt_copy_stream (ifp, ofp);
    safe_fclose (&ofp);
    safe_fclose (&ifp);
  }

  rv = 1;
  
bail:
  
  if (outfile && *outfile)
    close (out);

  /*
   * check for error exit from child process
   */
  if (mutt_wait_filter (thepid) != 0)
    rv = 0;

  if (rv == 0 || option (OPTWAITKEY))
    mutt_any_key_to_continue (NULL);
  return rv;
}