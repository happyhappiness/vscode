void mutt_encode_descriptions (BODY *b, short recurse)
{
  BODY *t;

  for (t = b; t; t = t->next)
  {
    if (t->description)
    {
      rfc2047_encode_string (&t->description);
    }
    if (recurse && t->parts)
      mutt_encode_descriptions (t->parts, recurse);
  }
}