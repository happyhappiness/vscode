int mutt_parent_message (CONTEXT *ctx, HEADER *hdr)
{
  THREAD *thread;

  if ((Sort & SORT_MASK) != SORT_THREADS)
  {
    mutt_error _("Threading is not enabled.");
    return (hdr->virtual);
  }

  for (thread = hdr->thread->parent; thread; thread = thread->parent)
  {
    if ((hdr = thread->message) != NULL)
    {
      if (VISIBLE (hdr, ctx))
	return (hdr->virtual);
      else
      {
	mutt_error _("Parent message is not visible in this limited view.");
	return (-1);
      }
    }
  }
  
  mutt_error _("Parent message is not available.");
  return (-1);
}