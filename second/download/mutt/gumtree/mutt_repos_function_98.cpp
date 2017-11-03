static void decode_descriptions (BODY *b)
{
  BODY *t;
  
  for (t = b; t; t = t->next)
  {
    if (t->description)
    {
      rfc2047_decode (&t->description);
    }
    if (t->parts)
      decode_descriptions (t->parts);
  }
}