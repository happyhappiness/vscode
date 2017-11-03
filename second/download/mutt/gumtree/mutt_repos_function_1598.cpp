static int pgp_parse_pgp2_sig (unsigned char *buff, size_t l,
                               pgp_key_t p, pgp_sig_t *s)
{
  unsigned char sigtype;
  time_t sig_gen_time;
  unsigned long signerid1;
  unsigned long signerid2;
  size_t j;
  int i;

  if (l < 22)
    return -1;

  j = 3;
  sigtype = buff[j++];

  sig_gen_time = 0;
  for (i = 0; i < 4; i++)
    sig_gen_time = (sig_gen_time << 8) + buff[j++];

  signerid1 = signerid2 = 0;
  for (i = 0; i < 4; i++)
    signerid1 = (signerid1 << 8) + buff[j++];

  for (i = 0; i < 4; i++)
    signerid2 = (signerid2 << 8) + buff[j++];

  
  if (sigtype == 0x20 || sigtype == 0x28)
    p->flags |= KEYFLAG_REVOKED;

  if (s)
  {
    s->sigtype = sigtype;
    s->sid1    = signerid1;
    s->sid2    = signerid2;
  }
  
  return 0;
}