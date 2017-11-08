static struct Cookie *dup_cookie(struct Cookie *src)
{
  struct Cookie *dup = calloc(sizeof(struct Cookie), 1);
  if(dup) {
    CLONE(expirestr);
    CLONE(domain);
    CLONE(path);
    CLONE(spath);
    CLONE(name);
    CLONE(value);
    CLONE(maxage);
    CLONE(version);
    dup->expires = src->expires;
    dup->tailmatch = src->tailmatch;
    dup->secure = src->secure;
    dup->livecookie = src->livecookie;
    dup->httponly = src->httponly;
  }
  return dup;

  fail:
  freecookie(dup);
  return NULL;
}