
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

