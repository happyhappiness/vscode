static void cldap_free(void *arg) /* {{{ */
{
  cldap_t *st = arg;

  if (st == NULL)
    return;

  sfree(st->binddn);
  sfree(st->password);
  sfree(st->cacert);
  sfree(st->host);
  sfree(st->name);
  sfree(st->url);
  if (st->ld)
    ldap_unbind_ext_s(st->ld, NULL, NULL);

  sfree(st);
}