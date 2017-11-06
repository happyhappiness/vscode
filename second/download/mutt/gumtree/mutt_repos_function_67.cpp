static int mutt_addrcmp (ADDRESS *a, ADDRESS *b)
{
  if (!a->mailbox || !b->mailbox)
    return 0;
  if (ascii_strcasecmp (a->mailbox, b->mailbox))
    return 0;
  return 1;
}