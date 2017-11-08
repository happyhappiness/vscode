struct conncache *Curl_mk_connc(int type,
                                long amount) /* set -1 to use default */
{
  /* It is subject for debate how many default connections to have for a multi
     connection cache... */

  struct conncache *c;
  long default_amount;

  if(type == CONNCACHE_PRIVATE) {
    default_amount = (amount < 0) ? 5 : amount;
  }
  else {
    default_amount = (amount < 0) ? 10 : amount;
  }

  c= calloc(sizeof(struct conncache), 1);
  if(!c)
    return NULL;

  if((size_t)(default_amount) > ((size_t)-1) / sizeof(struct connectdata *))
    default_amount = ((size_t)-1) / sizeof(struct connectdata *);

  c->connects = calloc(sizeof(struct connectdata *), (size_t)default_amount);
  if(!c->connects) {
    free(c);
    return NULL;
  }

  c->num = default_amount;

  return c;
}