static int cmp_case_string_key (union hash_key a, union hash_key b)
{
  return mutt_strcasecmp (a.strkey, b.strkey);
}