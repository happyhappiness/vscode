static unsigned int gen_int_hash (union hash_key key, unsigned int n)
{
  return key.intkey % n;
}