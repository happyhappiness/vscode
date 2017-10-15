    {
      if (fputc ('\n', msg->fp) == EOF)
	r = -1;
      break;
    }

#ifdef USE_IMAP
    case M_IMAP:
    {
      if ((r = safe_fclose (&msg->fp)) == 0)
	r = imap_append_message (ctx, msg);
      break;
