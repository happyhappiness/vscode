static int need_display_subject (CONTEXT *ctx, HEADER *hdr)
{
  THREAD *tmp, *tree = hdr->thread;

  /* if the user disabled subject hiding, display it */
  if (!option (OPTHIDETHREADSUBJECT))
    return (1);

  /* if our subject is different from our parent's, display it */
  if (hdr->subject_changed)
    return (1);

  /* if our subject is different from that of our closest previously displayed
   * sibling, display the subject */
  for (tmp = tree->prev; tmp; tmp = tmp->prev)
  {
    hdr = tmp->message;
    if (hdr && VISIBLE (hdr, ctx))
    {
      if (hdr->subject_changed)
	return (1);
      else
	break;
    }
  }
  
  /* if there is a parent-to-child subject change anywhere between us and our
   * closest displayed ancestor, display the subject */
  for (tmp = tree->parent; tmp; tmp = tmp->parent)
  {
    hdr = tmp->message;
    if (hdr)
    {
      if (VISIBLE (hdr, ctx))
	return (0);
      else if (hdr->subject_changed)
	return (1);
    }
  }

  /* if we have no visible parent or previous sibling, display the subject */
  return (1);
}