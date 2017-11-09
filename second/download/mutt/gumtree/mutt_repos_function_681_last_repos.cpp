HASH *hash_create (int nelem, int flags)
{
  HASH *table = new_hash (nelem);
  if (flags & MUTT_HASH_STRCASECMP)
  {
    table->gen_hash = gen_case_string_hash;
    table->cmp_key = cmp_case_string_key;
  }
  else
  {
    table->gen_hash = gen_string_hash;
    table->cmp_key = cmp_string_key;
  }
  if (flags & MUTT_HASH_STRDUP_KEYS)
    table->strdup_keys = 1;
  if (flags & MUTT_HASH_ALLOW_DUPS)
    table->allow_dups = 1;
  return table;
}