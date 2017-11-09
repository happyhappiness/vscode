static int pop_read_header (POP_DATA *pop_data, HEADER *h)
{
  FILE *f;
  int ret, index;
  long length;
  char buf[LONG_STRING];
  char tempfile[_POSIX_PATH_MAX];

  mutt_mktemp (tempfile, sizeof (tempfile));
  if (!(f = safe_fopen (tempfile, "w+")))
  {
    mutt_perror (tempfile);
    return -3;
  }

  snprintf (buf, sizeof (buf), "LIST %d\r\n", h->refno);
  ret = pop_query (pop_data, buf, sizeof (buf));
  if (ret == 0)
  {
    sscanf (buf, "+OK %d %ld", &index, &length);

    snprintf (buf, sizeof (buf), "TOP %d 0\r\n", h->refno);
    ret = pop_fetch_data (pop_data, buf, NULL, fetch_message, f);

    if (pop_data->cmd_top == 2)
    {
      if (ret == 0)
      {
	pop_data->cmd_top = 1;

	dprint (1, (debugfile, "pop_read_header: set TOP capability\n"));
      }

      if (ret == -2)
      {
	pop_data->cmd_top = 0;

	dprint (1, (debugfile, "pop_read_header: unset TOP capability\n"));
	snprintf (pop_data->err_msg, sizeof (pop_data->err_msg), "%s",
		_("Command TOP is not supported by server."));
      }
    }
  }

  switch (ret)
  {
    case 0:
    {
      rewind (f);
      h->env = mutt_read_rfc822_header (f, h, 0, 0);
      h->content->length = length - h->content->offset + 1;
      rewind (f);
      while (!feof (f))
      {
	h->content->length--;
	fgets (buf, sizeof (buf), f);
      }
      break;
    }
    case -2:
    {
      mutt_error ("%s", pop_data->err_msg);
      break;
    }
    case -3:
    {
      mutt_error _("Can't write header to temporary file!");
      break;
    }
  }

  safe_fclose (&f);
  unlink (tempfile);
  return ret;
}