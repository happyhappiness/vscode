static const char *pgp_hash_to_micalg (short id)
{
  int i;
  
  for (i = 0; HashAlgorithms[i].id >= 0; i++)
    if (HashAlgorithms[i].id == id)
      return HashAlgorithms[i].name;
  return "x-unknown";
}