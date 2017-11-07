static pgp_key_t pgp_parse_keyinfo (unsigned char *buff, size_t l)
{
  if (!buff || l < 2)
    return NULL;

  switch (buff[1])
  {
  case 2:
  case 3:
    return pgp_parse_pgp2_key (buff, l);
  case 4:
    return pgp_parse_pgp3_key (buff, l);
  default:
    return NULL;
  }
}