short pgp_cansign (unsigned char type)
{
  switch (type)
  {
  case 1:
  case 3:
  case 17:
  case 20:
    return 1;
  default:
    return 0;
  }
}