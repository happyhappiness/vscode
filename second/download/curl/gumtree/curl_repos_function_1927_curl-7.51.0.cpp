void Curl_cookie_cleanup(struct CookieInfo *c)
{
  if(c) {
    free(c->filename);
    Curl_cookie_freelist(c->cookies);
    free(c); /* free the base struct as well */
  }
}