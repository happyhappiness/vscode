static void run_mime_type_query (BODY *att)
{
  FILE *fp, *fperr;
  char cmd[HUGE_STRING];
  char *buf = NULL;
  size_t buflen;
  int dummy = 0;
  pid_t thepid;

  mutt_expand_file_fmt (cmd, sizeof(cmd), MimeTypeQueryCmd, att->filename);

  if ((thepid = mutt_create_filter (cmd, NULL, &fp, &fperr)) < 0)
  {
    mutt_error (_("Error running \"%s\"!"), cmd);
    return;
  }

  if ((buf = mutt_read_line (buf, &buflen, fp, &dummy, 0)) != NULL)
  {
    if (strchr(buf, '/'))
      mutt_parse_content_type (buf, att);
    FREE (&buf);
  }

  safe_fclose (&fp);
  safe_fclose (&fperr);
  mutt_wait_filter (thepid);
}