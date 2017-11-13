MESSAGE *mx_open_new_message (CONTEXT *dest, HEADER *hdr, int flags)
{
  MESSAGE *msg;
  int (*func) (MESSAGE *, CONTEXT *, HEADER *);
  ADDRESS *p = NULL;
  time_t t;

  switch (dest->magic)
  {
    case M_MMDF:
    case M_MBOX:
      func = mbox_open_new_message;
      break;
    case M_MAILDIR:
      func = maildir_open_new_message;
      break;
    case M_MH:
      func = mh_open_new_message;
      break;
#ifdef USE_IMAP
    case M_IMAP:
      func = imap_open_new_message;
      break;
#endif
    default:
      dprint (1, (debugfile, "mx_open_new_message(): function unimplemented for mailbox type %d.\n",
		  dest->magic));
      return (NULL);
  }

  msg = safe_calloc (1, sizeof (MESSAGE));
  msg->magic = dest->magic;
  msg->write = 1;

  if (hdr)
  {
    msg->flags.flagged = hdr->flagged;
    msg->flags.replied = hdr->replied;
    msg->flags.read    = hdr->read;
  }
  
  if (func (msg, dest, hdr) == 0)
  {
    if (dest->magic == M_MMDF)
      fputs (MMDF_SEP, msg->fp);

    if ((msg->magic == M_MBOX || msg->magic ==  M_MMDF) &&
	flags & M_ADD_FROM)
    {
      if (hdr)
      {
	if (hdr->env->return_path)
	  p = hdr->env->return_path;
	else if (hdr->env->sender)
	  p = hdr->env->sender;
	else
	  p = hdr->env->from;

	if (!hdr->received)
	  hdr->received = time (NULL);
	t = hdr->received;
      }
      else
	t = time (NULL);

      fprintf (msg->fp, "From %s %s", p ? p->mailbox : NONULL(Username), ctime (&t));
    }
  }
  else
    safe_free ((void **) &msg);

  return msg;
}