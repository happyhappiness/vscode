void Curl_rm_connc(struct conncache *c)
{
  if(c->connects) {
    long i;
    for(i = 0; i < c->num; ++i)
      conn_free(c->connects[i]);

    free(c->connects);
  }

  free(c);
}