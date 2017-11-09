HASH *int_hash_create (int nelem, int flags)
{
  HASH *table = new_hash (nelem);
  table->gen_hash = gen_int_hash;
  table->cmp_key = cmp_int_key;
  if (flags & MUTT_HASH_ALLOW_DUPS)
    table->allow_dups = 1;
  return table;
}