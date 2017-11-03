short pgp_get_abilities (unsigned char type)
{
  return (pgp_canencrypt (type) << 1) | pgp_cansign (type);
}