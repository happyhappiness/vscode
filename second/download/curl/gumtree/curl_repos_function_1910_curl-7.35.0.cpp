static void digest_cleanup_one(struct digestdata *d)
{
  Curl_safefree(d->nonce);
  Curl_safefree(d->cnonce);
  Curl_safefree(d->realm);
  Curl_safefree(d->opaque);
  Curl_safefree(d->qop);
  Curl_safefree(d->algorithm);

  d->nc = 0;
  d->algo = CURLDIGESTALGO_MD5; /* default algorithm */
  d->stale = FALSE; /* default means normal, not stale */
}