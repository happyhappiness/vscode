BODY *mutt_remove_multipart (BODY *b)
{
  BODY *t;

  if (b->parts)
  {
    t = b;
    b = b->parts;
    t->parts = NULL;
    mutt_free_body (&t);
  }
  return b;
}