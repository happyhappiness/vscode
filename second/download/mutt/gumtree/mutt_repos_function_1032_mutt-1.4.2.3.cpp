int maildir_open_new_message (MESSAGE *msg, CONTEXT *dest, HEADER *hdr)
{
  int fd;
  char path[_POSIX_PATH_MAX];
  char suffix[16];
  char subdir[16];

  if (hdr)
  {
    short deleted = hdr->deleted;
    hdr->deleted = 0;
    
    maildir_flags (suffix, sizeof (suffix), hdr);
    
    hdr->deleted = deleted;
  }
  else
    *suffix = '\0';
    
  if (hdr && (hdr->read || hdr->old))
    strfcpy (subdir, "cur", sizeof (subdir));
  else
    strfcpy (subdir, "new", sizeof (subdir));

  FOREVER
  {
    snprintf (path, _POSIX_PATH_MAX, "%s/tmp/%s.%ld.%d_%d.%s%s",
	     dest->path, subdir, time (NULL), getpid (), Counter++,
	     NONULL (Hostname), suffix);

    dprint (2, (debugfile, "maildir_open_new_message (): Trying %s.\n",
		path));

    if ((fd = open (path, O_WRONLY | O_EXCL | O_CREAT, 0600)) == -1)
    {
      if (errno != EEXIST)
      {
	mutt_perror (path);
	return -1;
      }
    }
    else
    {
      dprint (2, (debugfile, "maildir_open_new_message (): Success.\n"));
      msg->path = safe_strdup (path);
      break;
    }
  }

  if ((msg->fp = fdopen (fd, "w")) == NULL)
  {
    FREE (&msg->path);
    close (fd);
    unlink (path);
    return (-1);
  }

  return 0;
}