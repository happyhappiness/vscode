int mutt_parent_message (CONTEXT *ctx, HEADER *hdr, int find_root)
{
  THREAD *thread;
  HEADER *parent = NULL;

  if ((Sort & SORT_MASK) != SORT_THREADS)
  {
    mutt_error _("Threading is not enabled.");
    return (hdr->virtual);
  }

  /* Root may be the current message */
  if (find_root)
    parent = hdr;

  for (thread = hdr->thread->parent; thread; thread = thread->parent)
  {
    if ((hdr = thread->message) != NULL)
    {
      parent = hdr;
      if (!find_root)
        break;
    }
  }

  if (!parent)
  {
    mutt_error _("Parent message is not available.");
    return (-1);
  }
  if (!VISIBLE (parent, ctx))
  {
    if (find_root)
      mutt_error _("Root message is not visible in this limited view.");
    else
      mutt_error _("Parent message is not visible in this limited view.");
    return (-1);
  }
  return (parent->virtual);
}