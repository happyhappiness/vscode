static const struct pattern_flags *lookup_tag (char tag)
{
  int i;

  for (i = 0; Flags[i].tag; i++)
    if (Flags[i].tag == tag)
      return (&Flags[i]);
  return NULL;
}