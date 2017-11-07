static pgp_key_t *pgp_parse_pgp2_key (unsigned char *buff, size_t l)
{
  pgp_key_t *p;
  unsigned char alg;
  size_t expl;
  unsigned long id;
  time_t gen_time = 0;
  unsigned short exp_days = 0;
  size_t j;
  int i, k;
  unsigned char scratch[LONG_STRING];

  if (l < 12)
    return NULL;

  p = pgp_new_keyinfo();

  for (i = 0, j = 2; i < 4; i++)
    gen_time = (gen_time << 8) + buff[j++];

  p->gen_time = gen_time;

  for (i = 0; i < 2; i++)
    exp_days = (exp_days << 8) + buff[j++];

  if (exp_days && time (NULL) > gen_time + exp_days * 24 * 3600)
    p->flags |= KEYFLAG_EXPIRED;

  alg = buff[j++];

  p->numalg = alg;
  p->algorithm = pgp_pkalgbytype (alg);
  p->flags |= pgp_get_abilities (alg);

  expl = 0;
  for (i = 0; i < 2; i++)
    expl = (expl << 8) + buff[j++];

  p->keylen = expl;

  expl = (expl + 7) / 8;
  if (expl < 4)
    goto bailout;


  j += expl - 8;

  for (k = 0; k < 2; k++)
  {
    for (id = 0, i = 0; i < 4; i++)
      id = (id << 8) + buff[j++];

    snprintf ((char *) scratch + k * 8, sizeof (scratch) - k * 8,
	      "%08lX", id);
  }

  p->keyid = safe_strdup ((char *) scratch);

  return p;

bailout:

  safe_free ((void **) &p);
  return NULL;
}