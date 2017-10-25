void Curl_digest_cleanup_one(struct digestdata *d)
{
  if(d->nonce)
    free(d->nonce);
  d->nonce = NULL;

  if(d->cnonce)
    free(d->cnonce);
  d->cnonce = NULL;

  if(d->realm)
    free(d->realm);
  d->realm = NULL;

  if(d->opaque)
    free(d->opaque);
  d->opaque = NULL;

  if(d->qop)
    free(d->qop);
  d->qop = NULL;

  if(d->algorithm)
    free(d->algorithm);
  d->algorithm = NULL;

  d->nc = 0;
  d->algo = CURLDIGESTALGO_MD5; /* default algorithm */
  d->stale = FALSE; /* default means normal, not stale */
}