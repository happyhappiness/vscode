static void attach_collapse (BODY *b, short collapse, short init, short just_one)
{
  short i;
  for (; b; b = b->next)
  {
    i = init || b->collapsed;
    if (i && option (OPTDIGESTCOLLAPSE) && b->type == TYPEMULTIPART
	&& !ascii_strcasecmp (b->subtype, "digest"))
      attach_collapse (b->parts, 1, 1, 0);
    else if (b->type == TYPEMULTIPART || mutt_is_message_type (b->type, b->subtype))
      attach_collapse (b->parts, collapse, i, 0);
    b->collapsed = collapse;
    if (just_one)
      return;
  }
}