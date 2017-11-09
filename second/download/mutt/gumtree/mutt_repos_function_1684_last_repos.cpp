static pgp_key_t pgp_parse_pgp3_key (unsigned char *buff, size_t l)
{
  pgp_key_t p;
  unsigned char alg;
  unsigned char digest[SHA_DIGEST_LENGTH];
  unsigned char scratch[LONG_STRING];
  time_t gen_time = 0;
  unsigned long id;
  int i, k;
  short len;
  size_t j;

  p = pgp_new_keyinfo ();
  j = 2;

  for (i = 0; i < 4; i++)
    gen_time = (gen_time << 8) + buff[j++];

  p->gen_time = gen_time;

  alg = buff[j++];

  p->numalg = alg;
  p->algorithm = pgp_pkalgbytype (alg);
  p->flags |= pgp_get_abilities (alg);

  len = (buff[j] << 8) + buff[j + 1];
  p->keylen = len;

  if (alg >= 1 && alg <= 3)
    skip_bignum (buff, l, j, &j, 2);
  else if (alg == 16 || alg == 20)
    skip_bignum (buff, l, j, &j, 3);
  else if (alg == 17)
    skip_bignum (buff, l, j, &j, 4);

  pgp_make_pgp3_fingerprint (buff, j, digest);
  if (dump_fingerprints)
  {
    p->fingerprint = binary_fingerprint_to_string (digest, SHA_DIGEST_LENGTH);
  }
  
  for (k = 0; k < 2; k++)
  {
    for (id = 0, i = SHA_DIGEST_LENGTH - 8 + k * 4;
	 i < SHA_DIGEST_LENGTH + (k - 1) * 4; i++)
      id = (id << 8) + digest[i];

    snprintf ((char *) scratch + k * 8, sizeof (scratch) - k * 8, "%08lX", id);
  }

  p->keyid = safe_strdup ((char *) scratch);

  return p;
}