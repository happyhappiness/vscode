    if (magic == -1)
    {
      mutt_error (_("%s is not a mailbox!"), s);
      return 1;
    }
  }
  else if (magic != M_IMAP)
  {
    st->st_mtime = 0;
    st->st_atime = 0;

    if (errno == ENOENT)
    {
      if (option (OPTCONFIRMCREATE))
      {
	snprintf (tmp, sizeof (tmp), _("Create %s?"), s);
	if ((rc = mutt_yesorno (tmp, M_YES)) == M_NO)
	  ret = 1;
	else if (rc == -1)
	  ret = -1;
      }
    }
    else
    {
      mutt_perror (s);
      return 1;
    }
  }

  CLEARLINE (LINES-1);
  return (ret);
}

void state_prefix_putc (char c, STATE *s)
{
  if (s->flags & M_PENDINGPREFIX)
  {
    state_reset_prefix (s);
    if (s->prefix)
      state_puts (s->prefix, s);
  }

