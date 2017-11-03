static int count_body_parts (BODY *body, int flags)
{
  int count = 0;
  int shallcount, shallrecurse;
  BODY *bp;

  if (body == NULL)
    return 0;

  for (bp = body; bp != NULL; bp = bp->next)
  {
    /* Initial disposition is to count and not to recurse this part. */
    AT_COUNT("default");
    shallrecurse = 0;

    dprint(5, (debugfile, "bp: desc=\"%s\"; fn=\"%s\", type=\"%d/%s\"\n",
	   bp->description ? bp->description : ("none"),
	   bp->filename ? bp->filename :
			bp->d_filename ? bp->d_filename : "(none)",
	   bp->type, bp->subtype ? bp->subtype : "*"));

    if (bp->type == TYPEMESSAGE)
    {
      shallrecurse = 1;

      /* If it's an external body pointer, don't recurse it. */
      if (!ascii_strcasecmp (bp->subtype, "external-body"))
	shallrecurse = 0;

      /* Don't count containers if they're top-level. */
      if (flags & MUTT_PARTS_TOPLEVEL)
	AT_NOCOUNT("top-level message/*");
    }
    else if (bp->type == TYPEMULTIPART)
    {
      /* Always recurse multiparts, except multipart/alternative. */
      shallrecurse = 1;
      if (!ascii_strcasecmp(bp->subtype, "alternative"))
        shallrecurse = 0;

      /* Don't count containers if they're top-level. */
      if (flags & MUTT_PARTS_TOPLEVEL)
	AT_NOCOUNT("top-level multipart");
    }

    if (bp->disposition == DISPINLINE &&
        bp->type != TYPEMULTIPART && bp->type != TYPEMESSAGE && bp == body)
      AT_NOCOUNT("ignore fundamental inlines");

    /* If this body isn't scheduled for enumeration already, don't bother
     * profiling it further.
     */
    if (shallcount)
    {
      /* Turn off shallcount if message type is not in ok list,
       * or if it is in except list. Check is done separately for
       * inlines vs. attachments.
       */

      if (bp->disposition == DISPATTACH)
      {
        if (!count_body_parts_check(&AttachAllow, bp, 1))
	  AT_NOCOUNT("attach not allowed");
        if (count_body_parts_check(&AttachExclude, bp, 0))
	  AT_NOCOUNT("attach excluded");
      }
      else
      {
        if (!count_body_parts_check(&InlineAllow, bp, 1))
	  AT_NOCOUNT("inline not allowed");
        if (count_body_parts_check(&InlineExclude, bp, 0))
	  AT_NOCOUNT("excluded");
      }
    }

    if (shallcount)
      count++;
    bp->attach_qualifies = shallcount ? 1 : 0;

    dprint(5, (debugfile, "cbp: %p shallcount = %d\n", (void *)bp, shallcount));

    if (shallrecurse)
    {
      dprint(5, (debugfile, "cbp: %p pre count = %d\n", (void *)bp, count));
      bp->attach_count = count_body_parts(bp->parts, flags & ~MUTT_PARTS_TOPLEVEL);
      count += bp->attach_count;
      dprint(5, (debugfile, "cbp: %p post count = %d\n", (void *)bp, count));
    }
  }

  dprint(5, (debugfile, "bp: return %d\n", count < 0 ? 0 : count));
  return count < 0 ? 0 : count;
}