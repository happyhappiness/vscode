short pgp_canencrypt (unsigned char type)
{
  switch (type)
  {
  case 1:
  case 2:
  case 16:
  case 20:
    return 1;
  default:
    return 0;
  }
}