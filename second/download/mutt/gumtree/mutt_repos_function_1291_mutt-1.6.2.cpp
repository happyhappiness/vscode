void mutt_attach_init (BODY *b)
{
  for (; b; b = b->next)
  {
    b->tagged = 0;
    b->collapsed = 0;
    if (b->parts) 
      mutt_attach_init (b->parts);
  }
}