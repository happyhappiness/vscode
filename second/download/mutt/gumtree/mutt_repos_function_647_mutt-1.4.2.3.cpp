const char *pgp_pkalgbytype (unsigned char type)
{
  switch (type)
  {
  case 1:
    return "RSA";
  case 2:
    return "RSA";
  case 3:
    return "RSA";
  case 16:
    return "ElG";
  case 17:
    return "DSA";
  case 20:
    return "ElG";
  default:
    return "unk";
  }
}