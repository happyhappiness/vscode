static void set_noconv_flags (BODY *b, short flag)
{
  for(; b; b = b->next)
  {
    if (b->type == TYPEMESSAGE || b->type == TYPEMULTIPART)
      set_noconv_flags (b->parts, flag);
    else if (b->type == TYPETEXT && b->noconv)
    {
      if (flag)
	mutt_set_parameter ("x-mutt-noconv", "yes", &b->parameter);
      else
	mutt_delete_parameter ("x-mutt-noconv", &b->parameter);
    }
  }
}