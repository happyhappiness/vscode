static int pgp_parse_sig (unsigned char *buff, size_t l,
                          pgp_key_t p, pgp_sig_t *sig)
{
  if (!buff || l < 2 || !p)
    return -1;

  switch (buff[1])
  {
  case 2:
  case 3:
    return pgp_parse_pgp2_sig (buff, l, p, sig);      
  case 4:
    return pgp_parse_pgp3_sig (buff, l, p, sig);
  default:
    return -1;
  }
}