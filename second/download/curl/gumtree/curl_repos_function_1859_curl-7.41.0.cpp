void Curl_cookie_cleanup(struct CookieInfo *c)
{
  if(c) {
    if(c->filename)
      free(c->filename);
    Curl_cookie_freelist(c->cookies, TRUE);
    free(c); /* free the base struct as well */
  }
}