static short check_msg (BODY * b, short err)
{
  if (!mutt_is_message_type (b->type, b->subtype))
  {
    if (err)
      mutt_error _("You may only bounce message/rfc822 parts.");
    return -1;
  }
  return 0;
}