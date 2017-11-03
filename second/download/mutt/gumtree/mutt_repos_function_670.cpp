HASH *hash_create (int nelem, int lower)
{
  HASH *table = safe_malloc (sizeof (HASH));
  if (nelem == 0)
    nelem = 2;
  table->nelem = nelem;
  table->table = safe_calloc (nelem, sizeof (struct hash_elem *));
  if (lower)
  {
    table->hash_string = hash_case_string;
    table->cmp_string = mutt_strcasecmp;
  }
  else
  {
    table->hash_string = hash_string;
    table->cmp_string = mutt_strcmp;
  }
  return table;
}