static int cmp_string_key (union hash_key a, union hash_key b)
{
  return mutt_strcmp (a.strkey, b.strkey);
}